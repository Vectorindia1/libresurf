// engine/cef/cef_client.cpp

#include "cef_client.h"

#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"

namespace libresurf {

LibreSurfClient::LibreSurfClient() = default;

// ── CefLifeSpanHandler ────────────────────────────────────────────────────────

void LibreSurfClient::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    // Notify the tab manager that a new browser instance is ready.
    // TabManager::instance().onBrowserCreated(browser);
}

bool LibreSurfClient::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    return false;  // Allow the close.
}

void LibreSurfClient::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
}

// ── CefLoadHandler ────────────────────────────────────────────────────────────

void LibreSurfClient::OnLoadStart(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   TransitionType transition_type) {
    CEF_REQUIRE_UI_THREAD();
    if (!frame->IsMain()) return;
    // Signal UI: show loading spinner, update address bar.
}

void LibreSurfClient::OnLoadEnd(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame,
                                 int http_status_code) {
    CEF_REQUIRE_UI_THREAD();
    if (!frame->IsMain()) return;
    // Signal UI: hide spinner, update URL, update privacy stats.

    // Inject fingerprint protection scripts into the page.
    // FingerprintGuard::instance().inject(frame);
}

void LibreSurfClient::OnLoadError(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   ErrorCode error_code,
                                   const CefString& error_text,
                                   const CefString& failed_url) {
    CEF_REQUIRE_UI_THREAD();
    if (!frame->IsMain()) return;
    // Load the built-in error page.
    const std::string error_html = "<html><body><h2>Failed to load</h2><p>" +
                                   error_text.ToString() + "</p></body></html>";
    frame->LoadURL("data:text/html;charset=utf-8," + error_html);
}

// ── CefRequestHandler ─────────────────────────────────────────────────────────

CefRefPtr<CefResourceRequestHandler> LibreSurfClient::GetResourceRequestHandler(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    CefRefPtr<CefRequest> request,
    bool is_navigation,
    bool is_download,
    const CefString& request_initiator,
    bool& disable_default_handling) {
    // Return the tracker blocker resource handler.
    // return TrackerBlocker::instance().getHandler();
    return nullptr;
}

// ── CefDownloadHandler ────────────────────────────────────────────────────────

bool LibreSurfClient::CanDownload(CefRefPtr<CefBrowser> browser,
                                   const CefString& url,
                                   const CefString& request_method) {
    return true;  // All downloads allowed; download manager handles prompting.
}

void LibreSurfClient::OnBeforeDownload(CefRefPtr<CefBrowser> browser,
                                        CefRefPtr<CefDownloadItem> download_item,
                                        const CefString& suggested_name,
                                        CefRefPtr<CefBeforeDownloadCallback> callback) {
    CEF_REQUIRE_UI_THREAD();
    // Notify download manager → show download bar.
    // DownloadManager::instance().onBeforeDownload(download_item, suggested_name, callback);
    callback->Continue(suggested_name, true);  // show save dialog
}

void LibreSurfClient::OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefDownloadItem> download_item,
                                         CefRefPtr<CefDownloadItemCallback> callback) {
    CEF_REQUIRE_UI_THREAD();
    // DownloadManager::instance().onDownloadUpdated(download_item, callback);
}

}  // namespace libresurf
