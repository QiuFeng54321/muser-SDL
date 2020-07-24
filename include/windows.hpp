#ifndef WINDOWS_HPP
#define WINDOWS_HPP

#include "SDL.h"
#include <iostream>

namespace muser::windows {
    //Screen dimension constants
    extern const int kScreenWidth;
    extern const int kScreenHeight;
    extern SDL_Window *window;
    extern SDL_Renderer *renderer;
    int CreateMuserWindow();
    int CreateMuserRenderer();
    SDL_Surface* LoadBMP(std::string path);
    SDL_Texture* UploadToTexture(SDL_Surface* bmp);
}  // namespace muser::windows

#endif