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
    extern Preference main_pref, sprite_clips;
    extern std::string_view main_pref_path, sprite_clips_path;
    Preference InitPreference(const std::string_view& store_path, const std::string_view& entry_path);
    void InitPreferences();
    void SavePreference(Preference& pref);
    void SavePreferences();
    int GetBasicControl(std::string_view key);
    int GetGameplayControl(int index);
    sprite::Clip AsClip(toml::array arr);
    sprite::Clip AsMergedClip(toml::array arr);
}  // namespace muser::preference

#endif