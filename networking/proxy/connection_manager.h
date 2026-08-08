// networking/proxy/connection_manager.h
// Central proxy routing authority.
//
// ALL network traffic in LibreSurf is routed through the ConnectionManager.
// It is the single source of truth for which proxy (if any) is in use.
// No component may bypass it to make direct network connections.

#pragma once

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include "core/profiles/profile_manager.h"

namespace libresurf {

/// Result of a proxy connection test.
struct ConnectionTestResult {
    bool success{false};
    std::string externalIp;
    std::string protocol;
    std::string error;  ///< Empty on success.
};

/// Stores a named proxy profile for the connection manager.
struct NamedProxy {
    std::string id;
    std::string name;
    ProxyConfig config;
};

using TestCallback = std::function<void(ConnectionTestResult)>;

/// Manages all proxy configurations and enforces routing policy.
class ConnectionManager {
public:
    static ConnectionManager& instance();

    ConnectionManager();

    /// Set the active proxy for the given browser profile.
    void setProxy(const std::string& browserProfileId, const ProxyConfig& config);

    /// Get the active proxy for the given browser profile.
    ProxyConfig getProxy(const std::string& browserProfileId) const;

    /// Test a proxy configuration asynchronously.
    /// The callback is invoked on the calling thread's message loop.
    void testConnection(const NamedProxy& proxy, TestCallback callback);

    /// CRUD for named proxy profiles.
    NamedProxy* addProxy(const std::string& name, const ProxyConfig& config);
    void removeProxy(const std::string& proxyId);
    NamedProxy* getProxyById(const std::string& proxyId);
    std::vector<NamedProxy*> getAllProxies();

    /// Apply the active proxy to CEF.
    /// Called after profile switch or proxy config change.
    void applyToCef(const std::string& browserProfileId);

private:
    std::vector<NamedProxy> namedProxies_;
    // Maps browser profile ID → active proxy config.
    std::unordered_map<std::string, ProxyConfig> profileProxies_;
};

}  // namespace libresurf
