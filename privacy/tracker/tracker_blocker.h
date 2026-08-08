// privacy/tracker/tracker_blocker.h
// Tracker and ad blocking engine.
//
// Parses Adblock+ format filter lists and intercepts CEF resource requests.
// Used as a CefResourceRequestHandler. All blocking decisions are logged
// for the Privacy Dashboard.

#pragma once

#include <atomic>
#include <filesystem>
#include <string>
#include <vector>

#include "include/cef_resource_request_handler.h"

namespace libresurf {

/// Statistics for one page load.
struct BlockStats {
    std::atomic<int> trackersBlocked{0};
    std::atomic<int> adsBlocked{0};
    std::atomic<int> requestsTotal{0};
};

/// CEF resource request handler that enforces filter list rules.
class TrackerBlocker : public CefResourceRequestHandler {
public:
    static TrackerBlocker& instance();

    TrackerBlocker();

    /// Load a filter list from the given path (Adblock+ syntax).
    void loadList(const std::filesystem::path& listPath);

    /// Reload all configured lists from disk.
    void reloadLists();

    /// Returns true if the given request URL should be blocked.
    bool shouldBlock(const std::string& requestUrl, const std::string& frameOrigin) const;

    /// Get current block statistics (per page, reset on navigation).
    const BlockStats& getStats() const { return stats_; }

    /// Reset statistics (called on new page load).
    void resetStats();

    // ── CefResourceRequestHandler ─────────────────────────────────────────
    CefResourceRequestHandler::ReturnValue OnBeforeResourceLoad(
        CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefRequest> request,
        CefRefPtr<CefCallback> callback) override;

private:
    /// A compiled filter rule.
    struct FilterRule {
        std::string pattern;
        bool isException{false};    ///< @@ rules are exceptions (whitelist).
        bool isDomain{false};       ///< ||domain rules.
        std::vector<std::string> domains;  ///< $domain= option.
    };

    std::vector<FilterRule> rules_;
    BlockStats stats_;

    FilterRule parseRule(const std::string& line);
    bool matchesRule(const FilterRule& rule, const std::string& url,
                     const std::string& origin) const;

    IMPLEMENT_REFCOUNTING(TrackerBlocker);
};

}  // namespace libresurf
