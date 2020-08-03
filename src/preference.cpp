#include "preference.hpp"

namespace muser::preference {
    Preference main_pref, sprite_clips;
    constexpr std::string_view main_pref_path = "preference_main.toml";
    constexpr std::string_view sprite_clips_path = "preference_sprite_clips.toml";
    Preference InitPreference(const std::string_view& store_path, const std::string_view& entry_path) {
        std::ifstream in;
        in.open(main_pref_path.data());
        auto entry = resource::GetResource(entry_path);
        if(!in) {
            return {store_path, toml::parse(std::string_view{entry.start, entry.length})};
        } else {
            return {store_path, toml::parse(in)};
        }
    }
    void SavePreference(Preference& pref) {
        std::ofstream out(pref.store_path.data());
        out << pref.pref;
        out.close();
    }
    void InitPreferences() {
        main_pref = InitPreference(main_pref_path, "pref/main.toml");
        sprite_clips = InitPreference(sprite_clips_path, "pref/sprites.toml");
    }
    void SavePreferences() {
        SavePreference(main_pref);
        SavePreference(sprite_clips);
    }
    int GetBasicControl(std::string_view key) {
        return main_pref.pref["control"]["basic"][key].as_integer()->get();
    }
    int GetGameplayControl(int index) {
        return main_pref.pref["control"]["gameplay"][index].as_integer()->get();
    }
}