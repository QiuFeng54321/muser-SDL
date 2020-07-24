#include <windows.hpp>

namespace muser::windows {
    const int kScreenWidth = 256;
    const int kScreenHeight = 256;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    int CreateMuserWindow() {
        window = SDL_CreateWindow("Hello World!", 0, 0, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }
        return 0;
    }
    int CreateMuserRenderer() {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            SDL_DestroyWindow(window);
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }
        return 0;
    }
    SDL_Surface* LoadBMP(std::string path) {
        SDL_Surface* bmp = SDL_LoadBMP(path.c_str());
        if (bmp == nullptr) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
        }
        return bmp;
    }
    SDL_Texture* UploadToTexture(SDL_Surface* bmp) {
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, bmp);
        SDL_FreeSurface(bmp);
        if (tex == nullptr) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
        }
        return tex;
    }
}  // namespace muser::windows
