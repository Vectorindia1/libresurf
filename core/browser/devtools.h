// core/browser/devtools.h
// DevTools Manager
//
// Handles opening and closing the Chromium Developer Tools window.

#pragma once

#include "include/cef_browser.h"

namespace libresurf {

class DevTools {
public:
    /// Show DevTools for the specified browser instance.
    static void Show(CefRefPtr<CefBrowser> browser);

    /// Close DevTools if it is currently open for the browser instance.
    static void Close(CefRefPtr<CefBrowser> browser);

    /// Check if DevTools is currently open for the browser instance.
    static bool IsOpen(CefRefPtr<CefBrowser> browser);
};

}  // namespace libresurf
