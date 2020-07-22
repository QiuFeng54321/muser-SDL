#include "resource_manager.hpp"

namespace muser::resource {
    std::map<std::string, std::string> temp_file_map;
    std::string GetResource(const std::string &file_path, const std::string &fallback) {
        // Returns the resource data given the resource path
        auto result = resources.find(file_path);
        if (result != resources.end()) return result->second;
        return fallback;
    }
    void LoadResourcesToTempFiles() {
        for (auto pair : resources) {
            auto path = util::random_template_file();
            auto file = std::ofstream(path);
            file.write(pair.second.c_str(), pair.second.size());
            file.close();
            temp_file_map.insert(std::pair{pair.first, path});
        }
    }
    void ReleaseTempResources() {
        for (auto pair : temp_file_map) {
            std::filesystem::remove(std::filesystem::path(pair.second));
        }
    }
};  // namespace muser::resource