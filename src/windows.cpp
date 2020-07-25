#include <windows.hpp>

namespace muser::windows {
    const int kScreenWidth = 256;
    const int kScreenHeight = 256;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

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

    /** Draw an SDL_Texture to an SDL_Renderer at some destination rect
    * taking a clip of the texture if desired
    * @param tex The source texture we want to draw
    * @param ren The renderer we want to draw to
    * @param dst The destination rectangle to render the texture to
    * @param clip The sub-section of the texture to draw (clipping rect)
    *		default of nullptr draws the entire texture
    */
    void RenderTexture(SDL_Texture* tex, SDL_Rect dst,
                       SDL_Rect* clip, SDL_Renderer* ren) {
        SDL_RenderCopy(ren, tex, clip, &dst);
    }

    /**
    * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
    * the texture's width and height and taking a clip of the texture if desired
    * If a clip is passed, the clip's width and height will be used instead of
    *	the texture's
    * @param tex The source texture we want to draw
    * @param ren The renderer we want to draw to
    * @param x The x coordinate to draw to
    * @param y The y coordinate to draw to
    * @param clip The sub-section of the texture to draw (clipping rect)
    *		default of nullptr draws the entire texture
    */
    void RenderTexture(SDL_Texture* tex, int x, int y,
                       SDL_Rect* clip, SDL_Renderer* ren) {
        SDL_Rect dst;
        dst.x = x;
        dst.y = y;
        if (clip != nullptr) {
            dst.w = clip->w;
            dst.h = clip->h;
        } else {
            SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
        }
        RenderTexture(tex, dst, clip, ren);
    }

    /**
    * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
    * the texture's width and height and taking a clip of the texture if desired
    * If a clip is passed, the clip's width and height will be used instead of
    *	the texture's
    * @param tex The source texture we want to draw
    * @param ren The renderer we want to draw to
    * @param x The x coordinate to draw to
    * @param y The y coordinate to draw to
    * @param w The width of the to-be-drawn texture
    * @param h The height of the to-be-drawn texture
    * @param clip The sub-section of the texture to draw (clipping rect)
    *		default of nullptr draws the entire texture
    */
    void RenderTexture(SDL_Texture* tex, int x, int y, int w, int h,
                       SDL_Rect* clip, SDL_Renderer* ren) {
        SDL_Rect dst;
        dst.x = x;
        dst.y = y;
        dst.w = w == STRETCH_SCREEN_SIZE ? kScreenWidth : w;
        dst.h = h == STRETCH_SCREEN_SIZE ? kScreenHeight : h;
        if (clip != nullptr) {
            dst.w = w == TEXTURE_SIZE ? clip->w : dst.w;
            dst.h = h == TEXTURE_SIZE ? clip->h : dst.h;
        } else {
            SDL_QueryTexture(tex, nullptr, nullptr,
                w == TEXTURE_SIZE ? &dst.w : nullptr, h == TEXTURE_SIZE ? &dst.h : nullptr);
        }
        RenderTexture(tex, dst, clip, ren);
    }
}  // namespace muser::windows
