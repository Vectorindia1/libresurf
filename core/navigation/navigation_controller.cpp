// core/navigation/navigation_controller.cpp

#include "navigation_controller.h"
#include <regex>
#include "include/wrapper/cef_helpers.h"

namespace libresurf {

NavigationController::NavigationController(CefRefPtr<CefBrowser> browser) 
    : browser_(browser) {}

void NavigationController::navigateOrSearch(const std::string& input, const std::string& searchEngineUrl) {
    if (isUrl(input)) {
        // Ensure scheme exists
        std::string finalUrl = input;
        if (finalUrl.find("://") == std::string::npos) {
            finalUrl = "https://" + finalUrl;
        }
        loadUrl(finalUrl);
    } else {
        // Treat as search query
        // Basic URL encoding for the query could go here.
        std::string encodedQuery = input; // TODO: URL encode
        loadUrl(searchEngineUrl + encodedQuery);
    }
}

void NavigationController::loadUrl(const std::string& url) {
    if (browser_ && browser_->GetMainFrame()) {
        browser_->GetMainFrame()->LoadURL(url);
    }
}

void NavigationController::goBack() {
    if (browser_ && browser_->CanGoBack()) {
        browser_->GoBack();
    }
}

void NavigationController::goForward() {
    if (browser_ && browser_->CanGoForward()) {
        browser_->GoForward();
    }
}

void NavigationController::reload(bool ignoreCache) {
    if (browser_) {
        if (ignoreCache) {
            browser_->ReloadIgnoreCache();
        } else {
            browser_->Reload();
        }
    }
}

void NavigationController::stop() {
    if (browser_) {
        browser_->StopLoad();
    }
}

bool NavigationController::canGoBack() const {
    return browser_ ? browser_->CanGoBack() : false;
}

bool NavigationController::canGoForward() const {
    return browser_ ? browser_->CanGoForward() : false;
}

bool NavigationController::isUrl(const std::string& input) const {
    // Basic heuristic: contains a dot or a known scheme.
    if (input.find("://") != std::string::npos) return true;
    if (input.find("localhost") != std::string::npos) return true;
    
    // Check for a dot with no spaces (very naive, can be improved).
    if (input.find(' ') != std::string::npos) return false;
    return input.find('.') != std::string::npos;
}

}  // namespace libresurf
