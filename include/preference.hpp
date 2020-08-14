#ifndef PREFERENCE_HPP
#define PREFERENCE_HPP

#include <fstream>
#include <list>
#include <sstream>
#include <string>
#include <string_view>

#include "SDL.h"
#include "logger.hpp"
#include "resource_manager.hpp"
#include "sprite.hpp"
#include "toml.hpp"

namespace muser::preference {
    struct Preference {
        std::string_view store_path;
        toml::table pref;
    };
    extern SDL_Texture* sprite_sheet;
    extern Preference main_pref, sprite_clips;
    extern std::string_view main_pref_path, sprite_clips_path;
    Preference InitPreference(const std::string_view& store_path, const std::string_view& entry_path);
    void InitPreferences();
    void SavePreference(Preference& pref);
    void SavePreferences();
    int GetBasicControl(std::string_view key);
    int GetGameplayControl(int index);
    sprite::Clip AsClip(toml::array arr);
    toml::node_view<toml::node> GetWithPath(toml::node_view<toml::node> node, std::string path);
}  // namespace muser::preference

#endif