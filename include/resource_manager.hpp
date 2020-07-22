#ifndef RES_PATH_H
#define RES_PATH_H

#include <iostream>
#include <string>

#include "SDL.h"
#include "resource.hpp"

namespace muser::resource {
    class ResourceManager {
    public:
        static std::string GetResource(const std::string &file, const std::string &fallback = "");
    };
};  // namespace muser::resource

#endif