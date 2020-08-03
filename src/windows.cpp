#include "windows.hpp"
#include "sprite.hpp"

namespace muser::windows {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_DisplayMode display;
    int display_map_size;
    int display_map_x;
    int display_map_y;

    void Init() {
        SDL_GetCurrentDisplayMode(0, &display);
        display_map_size = std::min(display.w, display.h);
        display_map_x = display.w > display.h ? display.w / 2 - display_map_size / 2 : 0;
        display_map_y = display.h > display.w ? display.h / 2 - display_map_size / 2 : 0;
    }

    /**
     * @brief Initiates SDL_Window* for muser::windows::window and shows it.
     * 
     * @return int 1 if failed otherwise 0
     */
    int CreateMuserWindow() {
        window = SDL_CreateWindow("Muser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWindowWidth, kWindowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (window == nullptr) {
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }
        return 0;
    }

    /**
     * @brief Initiates SDL_Renderer* for muser::windows::renderer
     * 
     * @return int 0 if success else 1
     */
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

    int SetRenderTarget(SDL_Texture* texture) {
        return SDL_SetRenderTarget(renderer, texture);
    }

    int ResetRenderTarget() {
        return SDL_SetRenderTarget(renderer, nullptr);
    }

    /**
     * @brief Uses SDL_LoadBMP to load a bmp file into an SDL_Surface*
     * Prints error and quits if fail
     * @param path path to bmp
     * @return SDL_Surface* bmp loaded 
     */
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
    void RenderTexture(SDL_Texture* tex, SDL_Rect* dst,
                       SDL_Rect* clip, SDL_Renderer* ren,
                       double degree, SDL_RendererFlip flip) {
        SDL_RenderCopyEx(ren, tex, clip, dst, degree, nullptr, flip);
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
                       SDL_Rect* clip, SDL_Renderer* ren,
                       double degree, SDL_RendererFlip flip) {
        SDL_Rect *dst = new SDL_Rect;
        dst->x = x;
        dst->y = y;
        if (clip != nullptr) {
            dst->w = clip->w;
            dst->h = clip->h;
        } else {
            SDL_QueryTexture(tex, nullptr, nullptr, &dst->w, &dst->h);
        }
        RenderTexture(tex, dst, clip, ren, degree, flip);
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
                       SDL_Rect* clip, SDL_Renderer* ren,
                       double degree, SDL_RendererFlip flip) {
        SDL_Rect* dst = new SDL_Rect{x, y, w, h};
        sprite::Clip::ReplaceUniqueDimension(tex, dst, clip);
        RenderTexture(tex, dst, clip, ren, degree, flip);
    }

}  // namespace muser::windows
