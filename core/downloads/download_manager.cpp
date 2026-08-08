// core/downloads/download_manager.cpp

#include "download_manager.h"

namespace libresurf {

DownloadManager& DownloadManager::instance() {
    static DownloadManager instance;
    return instance;
}

void DownloadManager::setDelegate(DownloadManagerDelegate* delegate) {
    delegate_ = delegate;
}

void DownloadManager::onBeforeDownload(CefRefPtr<CefDownloadItem> download_item,
                                       const CefString& suggested_name,
                                       CefRefPtr<CefBeforeDownloadCallback> callback) {
    // Setting show_dialog to true lets the OS file picker handle the destination.
    callback->Continue(suggested_name, true);
    
    if (delegate_) {
        DownloadState state;
        state.id = download_item->GetId();
        state.url = download_item->GetURL().ToString();
        state.fullPath = suggested_name.ToString(); // Will be updated later
        state.totalBytes = download_item->GetTotalBytes();
        state.receivedBytes = 0;
        state.percentComplete = 0;
        state.isComplete = false;
        state.isCanceled = false;
        delegate_->onDownloadStarted(state);
    }
}

void DownloadManager::onDownloadUpdated(CefRefPtr<CefDownloadItem> download_item,
                                        CefRefPtr<CefDownloadItemCallback> callback) {
    uint32_t id = download_item->GetId();
    
    if (download_item->IsInProgress()) {
        activeDownloads_[id] = callback;
    } else {
        activeDownloads_.erase(id);
    }

    if (delegate_) {
        DownloadState state;
        state.id = id;
        state.url = download_item->GetURL().ToString();
        state.fullPath = download_item->GetFullPath().ToString();
        state.totalBytes = download_item->GetTotalBytes();
        state.receivedBytes = download_item->GetReceivedBytes();
        state.percentComplete = download_item->GetPercentComplete();
        state.isComplete = download_item->IsComplete();
        state.isCanceled = download_item->IsCanceled();

        if (state.isComplete || state.isCanceled) {
            delegate_->onDownloadCompleted(state);
        } else {
            delegate_->onDownloadUpdated(state);
        }
    }
}

void DownloadManager::cancelDownload(uint32_t id) {
    auto it = activeDownloads_.find(id);
    if (it != activeDownloads_.end() && it->second) {
        it->second->Cancel();
        activeDownloads_.erase(it);
    }
}

void DownloadManager::pauseDownload(uint32_t id) {
    auto it = activeDownloads_.find(id);
    if (it != activeDownloads_.end() && it->second) {
        it->second->Pause();
    }
}

void DownloadManager::resumeDownload(uint32_t id) {
    auto it = activeDownloads_.find(id);
    if (it != activeDownloads_.end() && it->second) {
        it->second->Resume();
    }
}

}  // namespace libresurf
