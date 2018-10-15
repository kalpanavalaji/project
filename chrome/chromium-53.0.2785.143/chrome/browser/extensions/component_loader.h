// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_COMPONENT_LOADER_H_
#define CHROME_BROWSER_EXTENSIONS_COMPONENT_LOADER_H_

#include <stddef.h>

#include <memory>
#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "build/build_config.h"

class ExtensionServiceInterface;
class PrefService;
class Profile;

namespace extensions {

class Extension;

// For registering, loading, and unloading component extensions.
class ComponentLoader {
 public:
  ComponentLoader(ExtensionServiceInterface* extension_service,
                  PrefService* prefs,
                  PrefService* local_state,
                  Profile* browser_context);
  virtual ~ComponentLoader();

  size_t registered_extensions_count() const {
    return component_extensions_.size();
  }

  // Creates and loads all registered component extensions.
  void LoadAll();

  // Registers and possibly loads a component extension. If ExtensionService
  // has been initialized, the extension is loaded; otherwise, the load is
  // deferred until LoadAll is called. The ID of the added extension is
  // returned.
  //
  // Component extension manifests must contain a "key" property with a unique
  // public key, serialized in base64. You can create a suitable value with the
  // following commands on a unixy system:
  //
  //   ssh-keygen -t rsa -b 1024 -N '' -f /tmp/key.pem
  //   openssl rsa -pubout -outform DER < /tmp/key.pem 2>/dev/null | base64 -w 0
  std::string Add(const std::string& manifest_contents,
                  const base::FilePath& root_directory);

  // Convenience method for registering a component extension by resource id.
  std::string Add(int manifest_resource_id,
                  const base::FilePath& root_directory);

  // Loads a component extension from file system. Replaces previously added
  // extension with the same ID.
  std::string AddOrReplace(const base::FilePath& path);

  // Returns the extension ID of a component extension specified by resource
  // id of its manifest file.
  std::string GetExtensionID(int manifest_resource_id,
                             const base::FilePath& root_directory);

  // Returns true if an extension with the specified id has been added.
  bool Exists(const std::string& id) const;

  // Unloads a component extension and removes it from the list of component
  // extensions to be loaded.
  void Remove(const base::FilePath& root_directory);
  void Remove(const std::string& id);

  // Call this during test setup to load component extensions that have
  // background pages for testing, which could otherwise interfere with tests.
  static void EnableBackgroundExtensionsForTesting();

  // Adds the default component extensions. If |skip_session_components|
  // the loader will skip loading component extensions that weren't supposed to
  // be loaded unless we are in signed user session (ChromeOS). For all other
  // platforms this |skip_session_components| is expected to be unset.
  void AddDefaultComponentExtensions(bool skip_session_components);

  // Similar to above but adds the default component extensions for kiosk mode.
  void AddDefaultComponentExtensionsForKioskMode(bool skip_session_components);

  // Parse the given JSON manifest. Returns NULL if it cannot be parsed, or if
  // if the result is not a DictionaryValue.
  base::DictionaryValue* ParseManifest(
      const std::string& manifest_contents) const;

  // Clear the list of registered extensions.
  void ClearAllRegistered();

  // Reloads a registered component extension.
  void Reload(const std::string& extension_id);

#if defined(OS_CHROMEOS)
  // Calls |done_cb|, if not a null callback, on success.
  // NOTE: |done_cb| is not called if the component loader is shut down
  // during loading.
  void AddChromeVoxExtension(const base::Closure& done_cb);
  void AddChromeOsSpeechSynthesisExtension();
#endif

  void set_ignore_whitelist_for_testing(bool value) {
    ignore_whitelist_for_testing_ = value;
  }

 private:
  // Information about a registered component extension.
  struct ComponentExtensionInfo {
    ComponentExtensionInfo(const base::DictionaryValue* manifest,
                           const base::FilePath& root_directory);

    // The parsed contents of the extensions's manifest file.
    const base::DictionaryValue* manifest;

    // Directory where the extension is stored.
    base::FilePath root_directory;

    // The component extension's ID.
    std::string extension_id;
  };

  std::string Add(const std::string& manifest_contents,
                  const base::FilePath& root_directory,
                  bool skip_whitelist);
  std::string Add(const base::DictionaryValue* parsed_manifest,
                  const base::FilePath& root_directory,
                  bool skip_whitelist);

  // Loads a registered component extension.
  void Load(const ComponentExtensionInfo& info);

  void AddDefaultComponentExtensionsWithBackgroundPages(
      bool skip_session_components);
  void AddDefaultComponentExtensionsWithBackgroundPagesForKioskMode();
  void AddFileManagerExtension();
  void AddVideoPlayerExtension();
  void AddAudioPlayerExtension();
  void AddGalleryExtension();
  void AddWebstoreWidgetExtension();
  void AddHangoutServicesExtension();
  void AddHotwordHelperExtension();
  void AddImageLoaderExtension();
  void AddNetworkSpeechSynthesisExtension();

  void AddWithNameAndDescription(int manifest_resource_id,
                                 const base::FilePath& root_directory,
                                 const std::string& name_string,
                                 const std::string& description_string);
  void AddChromeApp();
  void AddHotwordAudioVerificationApp();
  void AddKeyboardApp();
  void AddWebStoreApp();

  scoped_refptr<const Extension> CreateExtension(
      const ComponentExtensionInfo& info, std::string* utf8_error);

  // Unloads |component| from the memory.
  void UnloadComponent(ComponentExtensionInfo* component);

  // Enable HTML5 FileSystem for given component extension in Guest mode.
  void EnableFileSystemInGuestMode(const std::string& id);

#if defined(OS_CHROMEOS)
  // Adds an extension where the manifest file is stored on the file system.
  // |manifest_filename| can be relative to the |root_directory|.
  void AddWithManifestFile(
      const base::FilePath::CharType* manifest_filename,
      const base::FilePath& root_directory,
      const char* extension_id,
      const base::Closure& done_cb);

  // Used as a reply callback by |AddWithManifestFile|.
  // Called with a |root_directory| and parsed |manifest| and invokes
  // |done_cb| after adding the extension.
  void FinishAddWithManifestFile(
      const base::FilePath& root_directory,
      const char* extension_id,
      const base::Closure& done_cb,
      std::unique_ptr<base::DictionaryValue> manifest);
#endif

  PrefService* profile_prefs_;
  PrefService* local_state_;
  Profile* profile_;

  ExtensionServiceInterface* extension_service_;

  // List of registered component extensions (see Manifest::Location).
  typedef std::vector<ComponentExtensionInfo> RegisteredComponentExtensions;
  RegisteredComponentExtensions component_extensions_;

  bool ignore_whitelist_for_testing_;

  base::WeakPtrFactory<ComponentLoader> weak_factory_;

  friend class TtsApiTest;

  DISALLOW_COPY_AND_ASSIGN(ComponentLoader);
};

}  // namespace extensions

#endif  // CHROME_BROWSER_EXTENSIONS_COMPONENT_LOADER_H_
