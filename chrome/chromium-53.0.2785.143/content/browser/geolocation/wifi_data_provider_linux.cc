// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Provides wifi scan API binding for suitable for typical linux distributions.
// Currently, only the NetworkManager API is used, accessed via D-Bus (in turn
// accessed via the GLib wrapper).

#include "content/browser/geolocation/wifi_data_provider_linux.h"

#include <stddef.h>
#include <stdint.h>

#include <memory>

#include "base/macros.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/utf_string_conversions.h"
#include "content/browser/geolocation/wifi_data_provider_manager.h"
#include "dbus/bus.h"
#include "dbus/message.h"
#include "dbus/object_path.h"
#include "dbus/object_proxy.h"

namespace content {
namespace {
// The time periods between successive polls of the wifi data.
const int kDefaultPollingIntervalMilliseconds = 10 * 1000;  // 10s
const int kNoChangePollingIntervalMilliseconds = 2 * 60 * 1000;  // 2 mins
const int kTwoNoChangePollingIntervalMilliseconds = 10 * 60 * 1000;  // 10 mins
const int kNoWifiPollingIntervalMilliseconds = 20 * 1000; // 20s

const char kNetworkManagerServiceName[] = "org.freedesktop.NetworkManager";
const char kNetworkManagerPath[] = "/org/freedesktop/NetworkManager";
const char kNetworkManagerInterface[] = "org.freedesktop.NetworkManager";

// From http://projects.gnome.org/NetworkManager/developers/spec.html
enum { NM_DEVICE_TYPE_WIFI = 2 };

// Wifi API binding to NetworkManager, to allow reuse of the polling behavior
// defined in WifiDataProviderCommon.
// TODO(joth): NetworkManager also allows for notification based handling,
// however this will require reworking of the threading code to run a GLib
// event loop (GMainLoop).
class NetworkManagerWlanApi : public WifiDataProviderCommon::WlanApiInterface {
 public:
  NetworkManagerWlanApi();
  ~NetworkManagerWlanApi() override;

  // Must be called before any other interface method. Will return false if the
  // NetworkManager session cannot be created (e.g. not present on this distro),
  // in which case no other method may be called.
  bool Init();

  // Similar to Init() but can inject the bus object. Used for testing.
  bool InitWithBus(dbus::Bus* bus);

  // WifiDataProviderCommon::WlanApiInterface
  //
  // This function makes blocking D-Bus calls, but it's totally fine as
  // the code runs in "Geolocation" thread, not the browser's UI thread.
  bool GetAccessPointData(WifiData::AccessPointDataSet* data) override;

 private:
  // Enumerates the list of available network adapter devices known to
  // NetworkManager. Return true on success.
  bool GetAdapterDeviceList(std::vector<dbus::ObjectPath>* device_paths);

  // Given the NetworkManager path to a wireless adapater, dumps the wifi scan
  // results and appends them to |data|. Returns false if a fatal error is
  // encountered such that the data set could not be populated.
  bool GetAccessPointsForAdapter(const dbus::ObjectPath& adapter_path,
                                 WifiData::AccessPointDataSet* data);

  // Internal method used by |GetAccessPointsForAdapter|, given a wifi access
  // point proxy retrieves the named property and returns it. Returns NULL in
  // a scoped_ptr if the property could not be read.
  std::unique_ptr<dbus::Response> GetAccessPointProperty(
      dbus::ObjectProxy* proxy,
      const std::string& property_name);

  scoped_refptr<dbus::Bus> system_bus_;
  dbus::ObjectProxy* network_manager_proxy_;

  DISALLOW_COPY_AND_ASSIGN(NetworkManagerWlanApi);
};

// Convert a wifi frequency to the corresponding channel. Adapted from
// geolocaiton/wifilib.cc in googleclient (internal to google).
int frquency_in_khz_to_channel(int frequency_khz) {
  if (frequency_khz >= 2412000 && frequency_khz <= 2472000)  // Channels 1-13.
    return (frequency_khz - 2407000) / 5000;
  if (frequency_khz == 2484000)
    return 14;
  if (frequency_khz > 5000000 && frequency_khz < 6000000)  // .11a bands.
    return (frequency_khz - 5000000) / 5000;
  // Ignore everything else.
  return AccessPointData().channel;  // invalid channel
}

NetworkManagerWlanApi::NetworkManagerWlanApi()
    : network_manager_proxy_(NULL) {
}

NetworkManagerWlanApi::~NetworkManagerWlanApi() {
  // Close the connection.
  system_bus_->ShutdownAndBlock();
}

bool NetworkManagerWlanApi::Init() {
  dbus::Bus::Options options;
  options.bus_type = dbus::Bus::SYSTEM;
  options.connection_type = dbus::Bus::PRIVATE;
  return InitWithBus(new dbus::Bus(options));
}

bool NetworkManagerWlanApi::InitWithBus(dbus::Bus* bus) {
  system_bus_ = bus;
  // system_bus_ will own all object proxies created from the bus.
  network_manager_proxy_ =
      system_bus_->GetObjectProxy(kNetworkManagerServiceName,
                                  dbus::ObjectPath(kNetworkManagerPath));
  // Validate the proxy object by checking we can enumerate devices.
  std::vector<dbus::ObjectPath> adapter_paths;
  const bool success = GetAdapterDeviceList(&adapter_paths);
  VLOG(1) << "Init() result:  " << success;
  return success;
}

bool NetworkManagerWlanApi::GetAccessPointData(
    WifiData::AccessPointDataSet* data) {
  std::vector<dbus::ObjectPath> device_paths;
  if (!GetAdapterDeviceList(&device_paths)) {
    LOG(WARNING) << "Could not enumerate access points";
    return false;
  }
  int success_count = 0;
  int fail_count = 0;

  // Iterate the devices, getting APs for each wireless adapter found
  for (size_t i = 0; i < device_paths.size(); ++i) {
    const dbus::ObjectPath& device_path = device_paths[i];
    VLOG(1) << "Checking device: " << device_path.value();

    dbus::ObjectProxy* device_proxy =
        system_bus_->GetObjectProxy(kNetworkManagerServiceName,
                                    device_path);

    dbus::MethodCall method_call(DBUS_INTERFACE_PROPERTIES, "Get");
    dbus::MessageWriter builder(&method_call);
    builder.AppendString("org.freedesktop.NetworkManager.Device");
    builder.AppendString("DeviceType");
    std::unique_ptr<dbus::Response> response(device_proxy->CallMethodAndBlock(
        &method_call, dbus::ObjectProxy::TIMEOUT_USE_DEFAULT));
    if (!response) {
      LOG(WARNING) << "Failed to get the device type for "
                   << device_path.value();
      continue;  // Check the next device.
    }
    dbus::MessageReader reader(response.get());
    uint32_t device_type = 0;
    if (!reader.PopVariantOfUint32(&device_type)) {
      LOG(WARNING) << "Unexpected response for " << device_type << ": "
                   << response->ToString();
      continue;  // Check the next device.
    }
    VLOG(1) << "Device type: " << device_type;

    if (device_type == NM_DEVICE_TYPE_WIFI) {  // Found a wlan adapter
      if (GetAccessPointsForAdapter(device_path, data))
        ++success_count;
      else
        ++fail_count;
    }
  }
  // At least one successful scan overrides any other adapter reporting error.
  return success_count || fail_count == 0;
}

bool NetworkManagerWlanApi::GetAdapterDeviceList(
    std::vector<dbus::ObjectPath>* device_paths) {
  dbus::MethodCall method_call(kNetworkManagerInterface, "GetDevices");
  std::unique_ptr<dbus::Response> response(
      network_manager_proxy_->CallMethodAndBlock(
          &method_call, dbus::ObjectProxy::TIMEOUT_USE_DEFAULT));
  if (!response) {
    LOG(WARNING) << "Failed to get the device list";
    return false;
  }

  dbus::MessageReader reader(response.get());
  if (!reader.PopArrayOfObjectPaths(device_paths)) {
    LOG(WARNING) << "Unexpected response: " << response->ToString();
    return false;
  }
  return true;
}


bool NetworkManagerWlanApi::GetAccessPointsForAdapter(
    const dbus::ObjectPath& adapter_path, WifiData::AccessPointDataSet* data) {
  // Create a proxy object for this wifi adapter, and ask it to do a scan
  // (or at least, dump its scan results).
  dbus::ObjectProxy* device_proxy =
      system_bus_->GetObjectProxy(kNetworkManagerServiceName,
                                  adapter_path);
  dbus::MethodCall method_call(
      "org.freedesktop.NetworkManager.Device.Wireless",
      "GetAccessPoints");
  std::unique_ptr<dbus::Response> response(device_proxy->CallMethodAndBlock(
      &method_call, dbus::ObjectProxy::TIMEOUT_USE_DEFAULT));
  if (!response) {
    LOG(WARNING) << "Failed to get access points data for "
                 << adapter_path.value();
    return false;
  }
  dbus::MessageReader reader(response.get());
  std::vector<dbus::ObjectPath> access_point_paths;
  if (!reader.PopArrayOfObjectPaths(&access_point_paths)) {
    LOG(WARNING) << "Unexpected response for " << adapter_path.value() << ": "
                 << response->ToString();
    return false;
  }

  VLOG(1) << "Wireless adapter " << adapter_path.value() << " found "
          << access_point_paths.size() << " access points.";

  for (size_t i = 0; i < access_point_paths.size(); ++i) {
    const dbus::ObjectPath& access_point_path = access_point_paths[i];
    VLOG(1) << "Checking access point: " << access_point_path.value();

    dbus::ObjectProxy* access_point_proxy =
        system_bus_->GetObjectProxy(kNetworkManagerServiceName,
                                    access_point_path);

    AccessPointData access_point_data;
    {
      std::unique_ptr<dbus::Response> response(
          GetAccessPointProperty(access_point_proxy, "Ssid"));
      if (!response)
        continue;
      // The response should contain a variant that contains an array of bytes.
      dbus::MessageReader reader(response.get());
      dbus::MessageReader variant_reader(response.get());
      if (!reader.PopVariant(&variant_reader)) {
        LOG(WARNING) << "Unexpected response for " << access_point_path.value()
                     << ": " << response->ToString();
        continue;
      }
      const uint8_t* ssid_bytes = NULL;
      size_t ssid_length = 0;
      if (!variant_reader.PopArrayOfBytes(&ssid_bytes, &ssid_length)) {
        LOG(WARNING) << "Unexpected response for " << access_point_path.value()
                     << ": " << response->ToString();
        continue;
      }
      std::string ssid(ssid_bytes, ssid_bytes + ssid_length);
      access_point_data.ssid = base::UTF8ToUTF16(ssid);
    }

    { // Read the mac address
      std::unique_ptr<dbus::Response> response(
          GetAccessPointProperty(access_point_proxy, "HwAddress"));
      if (!response)
        continue;
      dbus::MessageReader reader(response.get());
      std::string mac;
      if (!reader.PopVariantOfString(&mac)) {
        LOG(WARNING) << "Unexpected response for " << access_point_path.value()
                     << ": " << response->ToString();
        continue;
      }

      base::ReplaceSubstringsAfterOffset(&mac, 0U, ":", base::StringPiece());
      std::vector<uint8_t> mac_bytes;
      if (!base::HexStringToBytes(mac, &mac_bytes) || mac_bytes.size() != 6) {
        LOG(WARNING) << "Can't parse mac address (found " << mac_bytes.size()
                     << " bytes) so using raw string: " << mac;
        access_point_data.mac_address = base::UTF8ToUTF16(mac);
      } else {
        access_point_data.mac_address = MacAddressAsString16(&mac_bytes[0]);
      }
    }

    {  // Read signal strength.
      std::unique_ptr<dbus::Response> response(
          GetAccessPointProperty(access_point_proxy, "Strength"));
      if (!response)
        continue;
      dbus::MessageReader reader(response.get());
      uint8_t strength = 0;
      if (!reader.PopVariantOfByte(&strength)) {
        LOG(WARNING) << "Unexpected response for " << access_point_path.value()
                     << ": " << response->ToString();
        continue;
      }
      // Convert strength as a percentage into dBs.
      access_point_data.radio_signal_strength = -100 + strength / 2;
    }

    { // Read the channel
      std::unique_ptr<dbus::Response> response(
          GetAccessPointProperty(access_point_proxy, "Frequency"));
      if (!response)
        continue;
      dbus::MessageReader reader(response.get());
      uint32_t frequency = 0;
      if (!reader.PopVariantOfUint32(&frequency)) {
        LOG(WARNING) << "Unexpected response for " << access_point_path.value()
                     << ": " << response->ToString();
        continue;
      }

      // NetworkManager returns frequency in MHz.
      access_point_data.channel =
          frquency_in_khz_to_channel(frequency * 1000);
    }
    VLOG(1) << "Access point data of " << access_point_path.value() << ": "
            << "SSID: " << access_point_data.ssid << ", "
            << "MAC: " << access_point_data.mac_address << ", "
            << "Strength: " << access_point_data.radio_signal_strength << ", "
            << "Channel: " << access_point_data.channel;

    data->insert(access_point_data);
  }
  return true;
}

std::unique_ptr<dbus::Response> NetworkManagerWlanApi::GetAccessPointProperty(
    dbus::ObjectProxy* access_point_proxy,
    const std::string& property_name) {
  dbus::MethodCall method_call(DBUS_INTERFACE_PROPERTIES, "Get");
  dbus::MessageWriter builder(&method_call);
  builder.AppendString("org.freedesktop.NetworkManager.AccessPoint");
  builder.AppendString(property_name);
  std::unique_ptr<dbus::Response> response =
      access_point_proxy->CallMethodAndBlock(
          &method_call, dbus::ObjectProxy::TIMEOUT_USE_DEFAULT);
  if (!response) {
    LOG(WARNING) << "Failed to get property for " << property_name;
  }
  return response;
}

}  // namespace

// static
WifiDataProvider* WifiDataProviderManager::DefaultFactoryFunction() {
  return new WifiDataProviderLinux();
}

WifiDataProviderLinux::WifiDataProviderLinux() {
}

WifiDataProviderLinux::~WifiDataProviderLinux() {
}

WifiDataProviderCommon::WlanApiInterface*
WifiDataProviderLinux::NewWlanApi() {
  std::unique_ptr<NetworkManagerWlanApi> wlan_api(new NetworkManagerWlanApi);
  if (wlan_api->Init())
    return wlan_api.release();
  return NULL;
}

WifiPollingPolicy* WifiDataProviderLinux::NewPollingPolicy() {
  return new GenericWifiPollingPolicy<kDefaultPollingIntervalMilliseconds,
                                      kNoChangePollingIntervalMilliseconds,
                                      kTwoNoChangePollingIntervalMilliseconds,
                                      kNoWifiPollingIntervalMilliseconds>;
}

WifiDataProviderCommon::WlanApiInterface*
WifiDataProviderLinux::NewWlanApiForTesting(dbus::Bus* bus) {
  std::unique_ptr<NetworkManagerWlanApi> wlan_api(new NetworkManagerWlanApi);
  if (wlan_api->InitWithBus(bus))
    return wlan_api.release();
  return NULL;
}

}  // namespace content
