#include "preference.hpp"

namespace muser::preference {
    Preference main_pref, sprite_clips;
    std::string_view main_pref_path = "preference_main.toml";
    std::string_view sprite_clips_path = "preference_sprite_clips.toml";
    Preference InitPreference(const std::string_view& store_path, const std::string_view& entry_path) {
        std::ifstream in;
        in.open(store_path.data());
        auto entry = resource::GetResource(entry_path);
        if (!in) {
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
        auto sprites_source = main_pref.pref["video"]["sprites_source"].value_or(std::string_view(""));
        if (sprites_source == "embedded"){
            auto sprite_clips_conf_path = main_pref.pref["video"]["sprites"].value_or(std::string_view(""));
            sprite_clips = InitPreference(sprite_clips_path, sprite_clips_conf_path);
        }
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
    sprite::Clip AsClip(toml::array arr) {
        return sprite::Clip{};
    }
}  // namespace muser::preference