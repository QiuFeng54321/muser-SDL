#ifndef RES_PATH_H
#define RES_PATH_H

#include <iostream>
#include <string>

#include "SDL.h"

namespace muser::resource {
    class ResourceManager {
    public:
        /**
         * Modified from https://www.willusher.io/sdl2%20tutorials/2014/06/16/postscript-0-properly-finding-resource-paths
         */
        static std::string GetResourcePath(const std::string &subDir = "");
    };
};  // namespace muser::resource

#endif