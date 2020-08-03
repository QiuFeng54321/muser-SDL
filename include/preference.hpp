#ifndef PREFERENCE_HPP
#define PREFERENCE_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <string_view>

#include "logger.hpp"
#include "resource_manager.hpp"
#include "toml.hpp"
#include "sprite.hpp"

namespace muser::preference {
    struct Preference {
        std::string_view store_path;
        toml::table pref;
    };
    extern Preference main_pref;
    extern const std::string_view main_pref_path;
    Preference InitPreference(const std::string_view& store_path, const std::string_view& entry_path);
    void InitPreferences();
    void SavePreference(Preference& pref);
    void SavePreferences();
    int GetBasicControl(std::string_view key);
    int GetGameplayControl(int index);
}  // namespace muser::preference

#endif