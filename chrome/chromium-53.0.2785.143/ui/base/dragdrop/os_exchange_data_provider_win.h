// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_DRAGDROP_OS_EXCHANGE_DATA_PROVIDER_WIN_H_
#define UI_BASE_DRAGDROP_OS_EXCHANGE_DATA_PROVIDER_WIN_H_

#include <objidl.h>
#include <shlobj.h>
#include <stddef.h>
#include <string>
#include <vector>

// Win8 SDK compatibility, see http://goo.gl/fufvl for more information.
// "Note: This interface has been renamed IDataObjectAsyncCapability."
// If we're building on pre-8 we define it to its old name. It's documented as
// being binary compatible.
#ifndef __IDataObjectAsyncCapability_FWD_DEFINED__
#define IDataObjectAsyncCapability IAsyncOperation
#endif

#include "base/macros.h"
#include "base/memory/scoped_vector.h"
#include "base/win/scoped_comptr.h"
#include "ui/base/dragdrop/os_exchange_data.h"
#include "ui/base/ui_base_export.h"
#include "ui/gfx/geometry/vector2d.h"
#include "ui/gfx/image/image_skia.h"

namespace ui {

class DataObjectImpl : public DownloadFileObserver,
                       public IDataObject,
                       public IDataObjectAsyncCapability {
 public:
  class Observer {
   public:
    virtual void OnWaitForData() = 0;
    virtual void OnDataObjectDisposed() = 0;
   protected:
    virtual ~Observer() { }
  };

  DataObjectImpl();

  // Accessors.
  void set_observer(Observer* observer) { observer_ = observer; }
  void set_in_drag_loop(bool in_drag_loop) { in_drag_loop_ = in_drag_loop; }

  // Number of known formats.
  size_t size() const { return contents_.size(); }

  // DownloadFileObserver implementation:
  void OnDownloadCompleted(const base::FilePath& file_path) override;
  void OnDownloadAborted() override;

  // IDataObject implementation:
  HRESULT __stdcall GetData(FORMATETC* format_etc, STGMEDIUM* medium) override;
  HRESULT __stdcall GetDataHere(FORMATETC* format_etc,
                                STGMEDIUM* medium) override;
  HRESULT __stdcall QueryGetData(FORMATETC* format_etc) override;
  HRESULT __stdcall GetCanonicalFormatEtc(FORMATETC* format_etc,
                                          FORMATETC* result) override;
  HRESULT __stdcall SetData(FORMATETC* format_etc,
                            STGMEDIUM* medium,
                            BOOL should_release) override;
  HRESULT __stdcall EnumFormatEtc(DWORD direction,
                                  IEnumFORMATETC** enumerator) override;
  HRESULT __stdcall DAdvise(FORMATETC* format_etc,
                            DWORD advf,
                            IAdviseSink* sink,
                            DWORD* connection) override;
  HRESULT __stdcall DUnadvise(DWORD connection) override;
  HRESULT __stdcall EnumDAdvise(IEnumSTATDATA** enumerator) override;

  // IDataObjectAsyncCapability implementation:
  HRESULT __stdcall EndOperation(HRESULT result,
                                 IBindCtx* reserved,
                                 DWORD effects) override;
  HRESULT __stdcall GetAsyncMode(BOOL* is_op_async) override;
  HRESULT __stdcall InOperation(BOOL* in_async_op) override;
  HRESULT __stdcall SetAsyncMode(BOOL do_op_async) override;
  HRESULT __stdcall StartOperation(IBindCtx* reserved) override;

  // IUnknown implementation:
  HRESULT __stdcall QueryInterface(const IID& iid, void** object) override;
  ULONG __stdcall AddRef() override;
  ULONG __stdcall Release() override;

 private:
  // FormatEtcEnumerator only likes us for our StoredDataMap typedef.
  friend class FormatEtcEnumerator;
  friend class OSExchangeDataProviderWin;

  ~DataObjectImpl() override;

  void StopDownloads();

  // Removes from contents_ the first data that matches |format|.
  void RemoveData(const FORMATETC& format);

  // Our internal representation of stored data & type info.
  struct StoredDataInfo {
    FORMATETC format_etc;
    STGMEDIUM* medium;
    bool owns_medium;
    scoped_refptr<DownloadFileProvider> downloader;

    StoredDataInfo(const FORMATETC& format_etc, STGMEDIUM* medium);
    ~StoredDataInfo();
  };

  typedef ScopedVector<StoredDataInfo> StoredData;
  StoredData contents_;

  base::win::ScopedComPtr<IDataObject> source_object_;

  bool is_aborting_;
  bool in_drag_loop_;
  bool in_async_mode_;
  bool async_operation_started_;
  Observer* observer_;
};

class UI_BASE_EXPORT OSExchangeDataProviderWin
    : public OSExchangeData::Provider {
 public:
  // Returns true if source has plain text that is a valid url.
  static bool HasPlainTextURL(IDataObject* source);

  // Returns true if source has plain text that is a valid URL and sets url to
  // that url.
  static bool GetPlainTextURL(IDataObject* source, GURL* url);

  static DataObjectImpl* GetDataObjectImpl(const OSExchangeData& data);
  static IDataObject* GetIDataObject(const OSExchangeData& data);
  static IDataObjectAsyncCapability* GetIAsyncOperation(
      const OSExchangeData& data);

  explicit OSExchangeDataProviderWin(IDataObject* source);
  OSExchangeDataProviderWin();

  ~OSExchangeDataProviderWin() override;

  IDataObject* data_object() const { return data_.get(); }
  IDataObjectAsyncCapability* async_operation() const { return data_.get(); }

  // OSExchangeData::Provider methods.
  Provider* Clone() const override;
  void MarkOriginatedFromRenderer() override;
  bool DidOriginateFromRenderer() const override;
  void SetString(const base::string16& data) override;
  void SetURL(const GURL& url, const base::string16& title) override;
  void SetFilename(const base::FilePath& path) override;
  void SetFilenames(const std::vector<FileInfo>& filenames) override;
  void SetPickledData(const Clipboard::FormatType& format,
                      const base::Pickle& data) override;
  void SetFileContents(const base::FilePath& filename,
                       const std::string& file_contents) override;
  void SetHtml(const base::string16& html, const GURL& base_url) override;

  bool GetString(base::string16* data) const override;
  bool GetURLAndTitle(OSExchangeData::FilenameToURLPolicy policy,
                      GURL* url,
                      base::string16* title) const override;
  bool GetFilename(base::FilePath* path) const override;
  bool GetFilenames(std::vector<FileInfo>* filenames) const override;
  bool GetPickledData(const Clipboard::FormatType& format,
                      base::Pickle* data) const override;
  bool GetFileContents(base::FilePath* filename,
                       std::string* file_contents) const override;
  bool GetHtml(base::string16* html, GURL* base_url) const override;
  bool HasString() const override;
  bool HasURL(OSExchangeData::FilenameToURLPolicy policy) const override;
  bool HasFile() const override;
  bool HasFileContents() const override;
  bool HasHtml() const override;
  bool HasCustomFormat(const Clipboard::FormatType& format) const override;
  void SetDownloadFileInfo(
      const OSExchangeData::DownloadFileInfo& download_info) override;
  void SetDragImage(const gfx::ImageSkia& image,
                    const gfx::Vector2d& cursor_offset) override;
  const gfx::ImageSkia& GetDragImage() const override;
  const gfx::Vector2d& GetDragImageOffset() const override;

 private:
  scoped_refptr<DataObjectImpl> data_;
  base::win::ScopedComPtr<IDataObject> source_object_;

  // Drag image and offset data. Only used for Ash.
  gfx::ImageSkia drag_image_;
  gfx::Vector2d drag_image_offset_;

  DISALLOW_COPY_AND_ASSIGN(OSExchangeDataProviderWin);
};

}  // namespace ui

#endif  // UI_BASE_DRAGDROP_OS_EXCHANGE_DATA_PROVIDER_WIN_H_
