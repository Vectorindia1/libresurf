// core/tabs/tab_manager.h
// Tab lifecycle manager.
//
// Owns all BrowserTab instances. Exactly one TabManager exists per window.
// Tabs are associated with a Profile and must not share CEF browser contexts
// across profiles.

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "include/cef_browser.h"

namespace libresurf {

/// State of a single browser tab.
enum class TabState { LOADING, LOADED, CRASHED, CLOSED };

/// Represents one browser tab.
struct BrowserTab {
    int id;
    CefRefPtr<CefBrowser> browser;
    TabState state{TabState::LOADING};
    std::string url;
    std::string title;
    std::string profileId;
    bool isLoading{false};
};

/// Callback interface for tab events. Implemented by the UI layer.
class TabManagerDelegate {
public:
    virtual ~TabManagerDelegate() = default;
    virtual void onTabCreated(int tabId) = 0;
    virtual void onTabClosed(int tabId) = 0;
    virtual void onTabSwitched(int tabId) = 0;
    virtual void onTabUpdated(int tabId, const std::string& url, const std::string& title,
                              TabState state) = 0;
};

/// Manages the lifecycle of all tabs in a browser window.
class TabManager {
public:
    explicit TabManager(TabManagerDelegate* delegate);
    ~TabManager();

    /// Open a new tab with the given URL in the given profile.
    /// Returns the new tab's ID.
    int newTab(const std::string& url, const std::string& profileId);

    /// Close the tab with the given ID.
    void closeTab(int tabId);

    /// Switch focus to the tab with the given ID.
    void switchTab(int tabId);

    /// Get the currently active tab. Returns nullptr if no tabs exist.
    BrowserTab* getActive();

    /// Get all open tabs (non-closed).
    std::vector<BrowserTab*> getAll();

    /// Get a tab by ID. Returns nullptr if not found.
    BrowserTab* getById(int tabId);

    // Called by CefClient on browser events.
    void onBrowserCreated(CefRefPtr<CefBrowser> browser, const std::string& profileId);
    void onLoadStart(int browserId);
    void onLoadEnd(int browserId, const std::string& url, const std::string& title);
    void onCrash(int browserId);

private:
    int nextTabId_{1};
    int activeTabId_{-1};
    std::unordered_map<int, std::unique_ptr<BrowserTab>> tabs_;
    TabManagerDelegate* delegate_{nullptr};

    int browserIdToTabId(int browserId);
};

}  // namespace libresurf
