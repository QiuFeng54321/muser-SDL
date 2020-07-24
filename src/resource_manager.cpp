#include "resource_manager.hpp"

namespace muser::resource {
    std::map<std::string, std::string> temp_file_map;
    bool enable_temp_file = true;
    std::string GetResource(const std::string &file_path, const std::string &fallback) {
        // Returns the resource data given the resource path
        auto result = resources.find(file_path);
        if (result != resources.end()) return result->second;
        return fallback;
    }

    void LoadResourceToTempFile(const std::string &resource_key, const std::string &data) {
        auto path = util::random_template_file();
        auto file = std::ofstream(path);
        file.write(data.c_str(), data.size());
        file.close();
        temp_file_map.insert_or_assign(resource_key, path);
    }

    void LoadResourcesToTempFiles() {
        for (auto pair : resources) {
            LoadResourceToTempFile(pair.first, pair.second);
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
        resources.insert_or_assign(key, value);
        if(enable_temp_file) {
            LoadResourceToTempFile(key, value);
        }
    }
};  // namespace muser::resource