// engine/cef/cef_client.h
// LibreSurf CefClient — the central callback hub for a browser window.
//
// Implements all CEF handler interfaces. One instance per browser window.

#pragma once

#include "include/cef_client.h"
#include "include/cef_download_handler.h"
#include "include/cef_life_span_handler.h"
#include "include/cef_load_handler.h"
#include "include/cef_permission_handler.h"
#include "include/cef_request_handler.h"
#include "include/cef_resource_request_handler.h"

namespace libresurf {

class LibreSurfClient : public CefClient,
                        public CefLifeSpanHandler,
                        public CefLoadHandler,
                        public CefRequestHandler,
                        public CefDownloadHandler {
public:
    explicit LibreSurfClient();

    // ── CefClient ────────────────────────────────────────────────────────────
    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
    CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }
    CefRefPtr<CefRequestHandler> GetRequestHandler() override { return this; }
    CefRefPtr<CefDownloadHandler> GetDownloadHandler() override { return this; }

    // ── CefLifeSpanHandler ───────────────────────────────────────────────────
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    bool DoClose(CefRefPtr<CefBrowser> browser) override;
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    // ── CefLoadHandler ───────────────────────────────────────────────────────
    void OnLoadStart(CefRefPtr<CefBrowser> browser,
                     CefRefPtr<CefFrame> frame,
                     TransitionType transition_type) override;
    void OnLoadEnd(CefRefPtr<CefBrowser> browser,
                   CefRefPtr<CefFrame> frame,
                   int http_status_code) override;
    void OnLoadError(CefRefPtr<CefBrowser> browser,
                     CefRefPtr<CefFrame> frame,
                     ErrorCode error_code,
                     const CefString& error_text,
                     const CefString& failed_url) override;

    // ── CefRequestHandler ────────────────────────────────────────────────────
    CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(
        CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefRequest> request,
        bool is_navigation,
        bool is_download,
        const CefString& request_initiator,
        bool& disable_default_handling) override;

    // ── CefDownloadHandler ───────────────────────────────────────────────────
    bool CanDownload(CefRefPtr<CefBrowser> browser,
                     const CefString& url,
                     const CefString& request_method) override;
    void OnBeforeDownload(CefRefPtr<CefBrowser> browser,
                          CefRefPtr<CefDownloadItem> download_item,
                          const CefString& suggested_name,
                          CefRefPtr<CefBeforeDownloadCallback> callback) override;
    void OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefDownloadItem> download_item,
                           CefRefPtr<CefDownloadItemCallback> callback) override;

private:
    IMPLEMENT_REFCOUNTING(LibreSurfClient);
};

}  // namespace libresurf
