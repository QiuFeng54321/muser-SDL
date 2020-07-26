#include "preference.hpp"

namespace muser::preference {
    toml::table main_pref;
    constexpr std::string_view main_pref_path = "preference_main.toml";
    void InitPreferences() {
        std::ifstream in;
        in.open(main_pref_path.data());
        auto embed_data_entry = resource::GetResource("pref/main.toml");
        if(!in) {
            main_pref = toml::parse(std::string_view{embed_data_entry.start, embed_data_entry.length});
        } else {
            main_pref = toml::parse(in);
        }
    }
    void SavePreferences() {
        std::ofstream out(main_pref_path.data());
        out << main_pref;
        out.close();
    }
    int GetBasicControl(std::string_view key) {
        return main_pref["control"]["basic"][key].as_integer()->get();
    }
    int GetGameplayControl(int index) {
        return main_pref["control"]["gameplay"][index].as_integer()->get();
    }
}