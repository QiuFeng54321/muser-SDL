#include "resource_manager.hpp"

namespace muser::resource {
    std::string ResourceManager::GetResource(const std::string &file_path, const std::string &fallback) {
        // Returns the resource data given the resource path
        auto result = resources.find(file_path);
        if(result != resources.end()) return result->second;
        return fallback;
    }
};  // namespace muser::resource