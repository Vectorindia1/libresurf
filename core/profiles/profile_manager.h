// core/profiles/profile_manager.h
// Browser profile management.
//
// Each profile has isolated storage, cookies, history, permissions, and
// network settings. Profiles must never share CEF request contexts.

#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace libresurf {

enum class ProfileType { DEFAULT, PRIVATE, TOR, CUSTOM };

/// Cookie policy for a profile.
enum class CookiePolicy {
    ALLOW_ALL,         ///< No restrictions.
    BLOCK_THIRD_PARTY, ///< Block cross-origin cookies.
    BLOCK_ALL,         ///< Block all cookies.
};

/// Proxy configuration attached to a profile.
struct ProxyConfig {
    enum class Type { DIRECT, HTTP, HTTPS, SOCKS4, SOCKS5, TOR };

    Type type{Type::DIRECT};
    std::string host;
    int port{0};
    std::string username;
    std::string password;  // Stored in OS keychain; never persisted to disk.
};

/// DNS resolution configuration.
struct DnsConfig {
    enum class Mode { SYSTEM, CUSTOM, DOH, DOT, TOR };

    Mode mode{Mode::SYSTEM};
    std::string customServer;  ///< IP address for CUSTOM mode.
    std::string dohUrl;        ///< HTTPS URL for DOH mode.
    std::string dotServer;     ///< Hostname for DOT mode.
};

/// Represents a single browser profile.
struct Profile {
    std::string id;
    std::string name;
    ProfileType type{ProfileType::DEFAULT};
    std::filesystem::path dataDir;
    ProxyConfig proxy;
    DnsConfig dns;
    CookiePolicy cookiePolicy{CookiePolicy::BLOCK_THIRD_PARTY};
    bool fingerprintProtection{true};
    bool historyEnabled{true};
    bool webRtcEnabled{true};  ///< False for Tor profile.
};

/// Manages all browser profiles.
class ProfileManager {
public:
    static ProfileManager& instance();

    ProfileManager();

    /// Create and persist a new profile.
    Profile* create(const std::string& name, ProfileType type);

    /// Delete a profile and its data directory.
    void remove(const std::string& profileId);

    /// Set the active profile. Returns false if the ID does not exist.
    bool setActive(const std::string& profileId);

    /// Get the active profile. Always non-null after initialization.
    Profile* getActive();

    /// Get all profiles.
    std::vector<Profile*> getAll();

    /// Get a profile by ID.
    Profile* getById(const std::string& profileId);

    /// Save profile settings to disk.
    void save(const Profile& profile);

    /// Load all profiles from disk.
    void loadAll();

private:
    std::string activeProfileId_;
    std::unordered_map<std::string, std::unique_ptr<Profile>> profiles_;

    std::filesystem::path profilesRoot_;

    void createBuiltinProfiles();
    std::string generateId();
};

}  // namespace libresurf
