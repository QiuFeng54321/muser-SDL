#ifndef RES_PATH_H
#define RES_PATH_H

#include <iostream>
#include <string>

#include "SDL.h"
#include <map>
#include <string>
#include <fstream>
#include "resource.hpp"
#include "util.hpp"
#include "logger.hpp"

namespace muser::resource {
    extern std::map<std::string, std::string> temp_file_map;
    std::string GetResource(const std::string &file, const std::string &fallback = "");
    void LoadResourcesToTempFiles();
    void ReleaseTempResources();
};  // namespace muser::resource

#endif