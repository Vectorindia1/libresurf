// core/downloads/download_manager.h
// Download Manager
//
// Tracks active downloads, updates the UI, and handles pausing/resuming/canceling.

#pragma once

#include <string>
#include <unordered_map>
#include "include/cef_download_item.h"

namespace libresurf {

struct DownloadState {
    uint32_t id;
    std::string url;
    std::string fullPath;
    int64_t totalBytes;
    int64_t receivedBytes;
    int percentComplete;
    bool isComplete;
    bool isCanceled;
};

class DownloadManagerDelegate {
public:
    virtual ~DownloadManagerDelegate() = default;
    virtual void onDownloadStarted(const DownloadState& state) = 0;
    virtual void onDownloadUpdated(const DownloadState& state) = 0;
    virtual void onDownloadCompleted(const DownloadState& state) = 0;
};

class DownloadManager {
public:
    static DownloadManager& instance();

    void setDelegate(DownloadManagerDelegate* delegate);

    void onBeforeDownload(CefRefPtr<CefDownloadItem> download_item,
                          const CefString& suggested_name,
                          CefRefPtr<CefBeforeDownloadCallback> callback);

    void onDownloadUpdated(CefRefPtr<CefDownloadItem> download_item,
                           CefRefPtr<CefDownloadItemCallback> callback);

    void cancelDownload(uint32_t id);
    void pauseDownload(uint32_t id);
    void resumeDownload(uint32_t id);

private:
    DownloadManager() = default;
    ~DownloadManager() = default;

    DownloadManagerDelegate* delegate_{nullptr};
    
    // Maps download ID to its CEF callback to allow pausing/canceling later.
    std::unordered_map<uint32_t, CefRefPtr<CefDownloadItemCallback>> activeDownloads_;
};

}  // namespace libresurf
