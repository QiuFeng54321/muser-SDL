#include "preference.hpp"

namespace muser::preference {
    SDL_Texture* sprite_sheet = nullptr;
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
        if (sprites_source == "embedded") {
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


    // TODO (Qiufeng54321): Any better way of doing this?
    template <typename T>
    T _Get(toml::array& arr, int index, T def = -3) {
        return arr[index].value_or(def);
    }

    sprite::Clip ClipFromTomlArray(int cx, int cy, int cw, int ch, int dx, int dy, int dw, int dh, double deg, SDL_RendererFlip flip) {
        return sprite::Clip(sprite_sheet,
                            new SDL_Rect{cx, cy, cw, ch},
                            new SDL_Rect{dx, dy, dw, dh}, deg, flip);
    };

    sprite::Clip AsSingleClip(toml::array& arr) {
        return ClipFromTomlArray(_Get<int>(arr, 0), _Get<int>(arr, 1), _Get<int>(arr, 2), _Get<int>(arr, 3),
                                 0, 0, _Get<int>(arr, 4), _Get<int>(arr, 5),
                                 _Get(arr, 6, 0.0), (SDL_RendererFlip)_Get<int>(arr, 7));
    }

    sprite::Clip AsPartialClip(toml::array& arr) {
        return ClipFromTomlArray(_Get<int>(arr, 0), _Get<int>(arr, 1), _Get<int>(arr, 2), _Get<int>(arr, 3),
                                 _Get<int>(arr, 4), _Get<int>(arr, 5), _Get<int>(arr, 6), _Get<int>(arr, 7),
                                 _Get(arr, 8, 0.0), (SDL_RendererFlip)_Get<int>(arr, 9));
    }

    sprite::Clip AsClip(toml::node& node) {
        if (node.is_array()) return AsSingleClip(*node.as_array());
        if (node.is_table()) {
            auto& tab = *node.as_table();
            auto& clips_arr = *tab["clips"].as_array();
            auto& size_node = *tab["size"].as_array();
            SDL_Rect* size = new SDL_Rect{0, 0, _Get<int>(size_node, 0), _Get<int>(size_node, 0)};
            std::list<sprite::Clip> clips;
            for (auto& ele : clips_arr) {
                clips.push_back(AsPartialClip(*ele.as_array()));
            }
            return sprite::Clip::FromClips(clips, size);
        }
        return sprite::Clip{};
    }

    toml::node_view<toml::node> GetWithPath(toml::node_view<toml::node> node, std::string path) {
        auto elements = util::Split(path, '.');
        toml::node_view res = node;
        for(const auto& ele : elements) {
            if(util::has_only_digits(ele)) {
                res = res[std::atoi(ele.c_str())];
            } else {
                res = res[ele];
            }
        }
        return res;
    }
}  // namespace muser::preference