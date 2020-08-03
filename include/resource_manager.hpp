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
    extern std::map<std::string_view, std::string_view> temp_file_map;
    extern std::map<std::string_view, SDL_Surface*> surface_buffer;
    extern bool enable_temp_file;
    ResourceEntry GetResource(const std::string_view &file, const ResourceEntry &fallback = {nullptr, 0});
    SDL_Surface *GetSurface(const std::string_view &key, SDL_Surface *fallback = nullptr);
    void LoadResourceToTempFile(const std::string_view &resource_key, const std::string_view &data);
    void LoadResourceToTempFile(const std::string_view &resource_key, const ResourceEntry &data);
    void LoadResourcesToTempFiles();
    void LoadBMP(const std::string_view &key, const std::string &data);
    void LoadBMP(const std::string_view &key, const ResourceEntry &data);
    void LoadBMPs();
    std::string_view GetTempFile(const std::string_view &key);
    void ReleaseTempResources();
    void AddResource(const std::string_view &key, const std::string_view &value);
    void AddResource(const std::string_view &key, const ResourceEntry &value);
};  // namespace muser::resource

#endif