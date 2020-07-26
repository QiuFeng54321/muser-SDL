#ifndef PREFERENCE_HPP
#define PREFERENCE_HPP

#include <fstream>
#include <string>
#include <string_view>
#include <sstream>
#include "toml.hpp"
#include "resource_manager.hpp"
#include "logger.hpp"

namespace muser::preference {
    extern toml::table main_pref;
    extern const std::string_view main_pref_path;
    void InitPreferences();
    void SavePreferences();
    int GetBasicControl(std::string_view key);
    int GetGameplayControl(int index);
}  // namespace muser::preference

#endif