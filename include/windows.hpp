#ifndef WINDOWS_HPP
#define WINDOWS_HPP

#define STRETCH_SCREEN_SIZE -1
#define TEXTURE_SIZE 0

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
    void RenderTexture(SDL_Texture* tex, SDL_Rect dst,
                       SDL_Rect* clip = nullptr, SDL_Renderer* ren = renderer);
    void RenderTexture(SDL_Texture* tex, int x = 0, int y = 0,
                        SDL_Rect* clip = nullptr, SDL_Renderer* ren = renderer);
    void RenderTexture(SDL_Texture* tex, int x = 0, int y = 0, 
                        int w = TEXTURE_SIZE, int h = TEXTURE_SIZE,
                        SDL_Rect* clip = nullptr, SDL_Renderer* ren = renderer);
}  // namespace muser::windows

#endif