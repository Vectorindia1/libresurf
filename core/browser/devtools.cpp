// core/browser/devtools.cpp

#include "devtools.h"

namespace libresurf {

void DevTools::Show(CefRefPtr<CefBrowser> browser) {
    if (!browser || !browser->GetHost()) return;
    
    CefWindowInfo windowInfo;
#if defined(OS_WIN)
    windowInfo.SetAsPopup(nullptr, "DevTools");
#elif defined(OS_LINUX)
    // On Linux, setting parent to nullptr creates a new top-level window.
    windowInfo.SetAsWindowless(0); // Not windowless, but pop up a window.
#endif

    CefRefPtr<CefClient> client; // Optionally pass a client for the DevTools window itself
    CefBrowserSettings settings;
    CefPoint inspectElementAt;

    browser->GetHost()->ShowDevTools(windowInfo, client, settings, inspectElementAt);
}

void DevTools::Close(CefRefPtr<CefBrowser> browser) {
    if (!browser || !browser->GetHost()) return;
    browser->GetHost()->CloseDevTools();
}

bool DevTools::IsOpen(CefRefPtr<CefBrowser> browser) {
    if (!browser || !browser->GetHost()) return false;
    return browser->GetHost()->HasDevTools();
}

}  // namespace libresurf
