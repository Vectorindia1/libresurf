// core/tabs/tab_manager.cpp

#include "tab_manager.h"

#include <algorithm>
#include <stdexcept>

namespace libresurf {

TabManager::TabManager(TabManagerDelegate* delegate) : delegate_(delegate) {}

TabManager::~TabManager() = default;

int TabManager::newTab(const std::string& url, const std::string& profileId) {
    int tabId = nextTabId_++;
    auto tab = std::make_unique<BrowserTab>();
    tab->id = tabId;
    tab->url = url;
    tab->profileId = profileId;
    tab->state = TabState::LOADING;
    tab->isLoading = true;

    // TODO: Create CEF browser for this tab using the profile's request context.
    // CefWindowInfo window_info;
    // CefBrowserSettings settings;
    // auto request_context = ProfileManager::instance().getProfile(profileId)->requestContext();
    // tab->browser = CefBrowserHost::CreateBrowserSync(window_info, client_, url, settings,
    //                                                  nullptr, request_context);

    tabs_[tabId] = std::move(tab);

    if (delegate_) delegate_->onTabCreated(tabId);
    switchTab(tabId);
    return tabId;
}

void TabManager::closeTab(int tabId) {
    auto it = tabs_.find(tabId);
    if (it == tabs_.end()) return;

    it->second->state = TabState::CLOSED;
    if (it->second->browser) {
        it->second->browser->GetHost()->CloseBrowser(false);
    }

    // Switch to another tab if this was active.
    if (activeTabId_ == tabId) {
        activeTabId_ = -1;
        for (auto& [id, tab] : tabs_) {
            if (id != tabId && tab->state != TabState::CLOSED) {
                switchTab(id);
                break;
            }
        }
    }

    if (delegate_) delegate_->onTabClosed(tabId);
    tabs_.erase(it);
}

void TabManager::switchTab(int tabId) {
    if (tabs_.find(tabId) == tabs_.end()) return;
    activeTabId_ = tabId;
    if (delegate_) delegate_->onTabSwitched(tabId);
}

BrowserTab* TabManager::getActive() {
    if (activeTabId_ == -1) return nullptr;
    auto it = tabs_.find(activeTabId_);
    return (it != tabs_.end()) ? it->second.get() : nullptr;
}

std::vector<BrowserTab*> TabManager::getAll() {
    std::vector<BrowserTab*> result;
    result.reserve(tabs_.size());
    for (auto& [id, tab] : tabs_) {
        if (tab->state != TabState::CLOSED) {
            result.push_back(tab.get());
        }
    }
    return result;
}

BrowserTab* TabManager::getById(int tabId) {
    auto it = tabs_.find(tabId);
    return (it != tabs_.end()) ? it->second.get() : nullptr;
}

void TabManager::onBrowserCreated(CefRefPtr<CefBrowser> browser, const std::string& profileId) {
    // Map browser ID to tab ID and store the browser reference.
    // This is called by LibreSurfClient::OnAfterCreated.
}

void TabManager::onLoadStart(int browserId) {
    int tabId = browserIdToTabId(browserId);
    auto* tab = getById(tabId);
    if (!tab) return;
    tab->state = TabState::LOADING;
    tab->isLoading = true;
    if (delegate_) delegate_->onTabUpdated(tabId, tab->url, tab->title, tab->state);
}

void TabManager::onLoadEnd(int browserId, const std::string& url, const std::string& title) {
    int tabId = browserIdToTabId(browserId);
    auto* tab = getById(tabId);
    if (!tab) return;
    tab->url = url;
    tab->title = title;
    tab->state = TabState::LOADED;
    tab->isLoading = false;
    if (delegate_) delegate_->onTabUpdated(tabId, url, title, tab->state);
}

void TabManager::onCrash(int browserId) {
    int tabId = browserIdToTabId(browserId);
    auto* tab = getById(tabId);
    if (!tab) return;
    tab->state = TabState::CRASHED;
    tab->isLoading = false;
    if (delegate_) delegate_->onTabUpdated(tabId, tab->url, tab->title, tab->state);
}

int TabManager::browserIdToTabId(int browserId) {
    // TODO: maintain a map of browser ID → tab ID.
    return browserId;
}

}  // namespace libresurf
