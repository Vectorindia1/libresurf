// core/navigation/navigation_controller.h
// Navigation Controller
//
// Handles URL parsing, history traversal (Back/Forward), and reloading for a specific tab.

#pragma once

#include <string>
#include "include/cef_browser.h"

namespace libresurf {

class NavigationController {
public:
    explicit NavigationController(CefRefPtr<CefBrowser> browser);

    /// Navigate to a user-provided string (could be URL or search query).
    void navigateOrSearch(const std::string& input, const std::string& searchEngineUrl = "https://duckduckgo.com/?q=");

    /// Navigate directly to an absolute URL.
    void loadUrl(const std::string& url);

    void goBack();
    void goForward();
    void reload(bool ignoreCache = false);
    void stop();

    bool canGoBack() const;
    bool canGoForward() const;

private:
    CefRefPtr<CefBrowser> browser_;
    
    bool isUrl(const std::string& input) const;
};

}  // namespace libresurf
