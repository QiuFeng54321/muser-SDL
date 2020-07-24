#ifndef RES_PATH_H
#define RES_PATH_H

#include <iostream>
#include <string>

#include "SDL.h"
#include <map>
#include <string>
#include <fstream>
#include <cstdio>
#include "resource.hpp"
#include "util.hpp"
#include "logger.hpp"

namespace muser::resource {
    extern std::map<std::string, std::string> temp_file_map;
    extern bool enable_temp_file;
    std::string GetResource(const std::string &file, const std::string &fallback = "");
    void LoadResourceToTempFile(const std::string &resource_key, const std::string &data);
    void LoadResourcesToTempFiles();
    std::string GetTempFile(const std::string &key);
    void ReleaseTempResources();
    void AddResource(const std::string &key, const std::string &value);
};  // namespace muser::resource

#endif