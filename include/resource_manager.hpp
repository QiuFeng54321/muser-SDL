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
    extern std::map<std::string, SDL_Surface*> surface_buffer;
    extern bool enable_temp_file;
    ResourceEntry GetResource(const std::string &file, const ResourceEntry &fallback = {nullptr, 0});
    SDL_Surface *GetSurface(const std::string &key, SDL_Surface *fallback = nullptr);
    void LoadResourceToTempFile(const std::string &resource_key, const std::string &data);
    void LoadResourceToTempFile(const std::string &resource_key, const ResourceEntry &data);
    void LoadResourcesToTempFiles();
    void LoadBMP(const std::string &key, const std::string &data);
    void LoadBMP(const std::string &key, const ResourceEntry &data);
    void LoadBMPs();
    std::string GetTempFile(const std::string &key);
    void ReleaseTempResources();
    void AddResource(const std::string &key, const std::string &value);
    void AddResource(const std::string &key, const ResourceEntry &value);
};  // namespace muser::resource

#endif