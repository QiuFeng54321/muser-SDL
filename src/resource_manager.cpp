#include "resource_manager.hpp"

namespace muser::resource {
    std::map<std::string, std::string> temp_file_map;
    std::map<std::string, SDL_Surface*> surface_buffer;
    bool enable_temp_file = true;

    ResourceEntry GetResource(const std::string &file_path, const ResourceEntry &fallback) {
        // Returns the resource data given the resource path
        auto result = resources.find(file_path);
        if (result != resources.end()) return result->second;
        return fallback;
    }

    SDL_Surface *GetSurface(const std::string &key, SDL_Surface *fallback) {
        auto result = surface_buffer.find(key);
        if (result != surface_buffer.end()) return result->second;
        return fallback;
    }

    void LoadResourceToTempFile(const std::string &resource_key, const std::string &data) {
        LoadResourceToTempFile(resource_key, ResourceEntry{data.c_str(), data.size()});
    }

    void LoadResourceToTempFile(const std::string &resource_key, const ResourceEntry &data) {
        auto path = util::random_template_file();
        auto file = std::ofstream(path);
        file.write(data.start, data.length);
        file.close();
        temp_file_map.insert_or_assign(resource_key, path);
    }

    void LoadResourcesToTempFiles() {
        for (auto pair : resources) {
            LoadResourceToTempFile(pair.first, pair.second);
        }
    }

    void LoadBMP(const std::string &key, const std::string &data) {
        LoadBMP(key, ResourceEntry{data.c_str(), data.size()});
    }

    void LoadBMP(const std::string &key, const ResourceEntry &data) {
        SDL_RWops *rw = SDL_RWFromConstMem(data.start, data.length);
        SDL_Surface *img = SDL_LoadBMP_RW(rw, 1);
        surface_buffer.insert_or_assign(key, img);
    }

    void LoadBMPs() {
        for (auto pair : resources) {
            auto ext_i = pair.first.rfind('.');
            if(ext_i != std::string::npos) {
                if(auto ext = pair.first.substr(ext_i + 1); ext == "bmp") {
                    LoadBMP(pair.first, pair.second);
                }
            }
        }
    }

    std::string GetTempFile(const std::string &key) {
        auto result = temp_file_map.find(key);
        if(result == temp_file_map.end()) {
            throw std::runtime_error("Attempting to get a temp file of a non-existant key");
        }
        return result->second;
    }

    void ReleaseTempResources() {
        for (auto pair : temp_file_map) {
            remove(pair.second.c_str());
            // std::filesystem::remove(std::filesystem::path(pair.second));
        }
    }

    void AddResource(const std::string &key, const std::string &value) {
        AddResource(key, ResourceEntry{value.c_str(), value.size()});
    }

    void AddResource(const std::string &key, const ResourceEntry &value) {
        resources.insert_or_assign(key, value);
        if(enable_temp_file) {
            LoadResourceToTempFile(key, value);
        }
    }
};  // namespace muser::resource