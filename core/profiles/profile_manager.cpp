// core/profiles/profile_manager.cpp

#include "profile_manager.h"

namespace libresurf {

ProfileManager& ProfileManager::instance() {
    static ProfileManager instance;
    return instance;
}

ProfileManager::ProfileManager() {
    // Initialize profile root directory (e.g., ~/.libresurf/profiles)
    // createBuiltinProfiles();
}

Profile* ProfileManager::create(const std::string& name, ProfileType type) {
    // TODO: implement
    return nullptr;
}

void ProfileManager::remove(const std::string& profileId) {
    // TODO: implement
}

bool ProfileManager::setActive(const std::string& profileId) {
    // TODO: implement
    return false;
}

Profile* ProfileManager::getActive() {
    // TODO: implement
    return nullptr;
}

std::vector<Profile*> ProfileManager::getAll() {
    // TODO: implement
    return {};
}

Profile* ProfileManager::getById(const std::string& profileId) {
    // TODO: implement
    return nullptr;
}

void ProfileManager::save(const Profile& profile) {
    // TODO: implement
}

void ProfileManager::loadAll() {
    // TODO: implement
}

void ProfileManager::createBuiltinProfiles() {
    // TODO: implement Default, Private, Tor profiles
}

std::string ProfileManager::generateId() {
    // TODO: implement UUID generation
    return "default-id";
}

}  // namespace libresurf
