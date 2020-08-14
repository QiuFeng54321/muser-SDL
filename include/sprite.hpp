#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "SDL.h"
#include "util.hpp"
#include <list>

namespace muser::sprite {
    SDL_Rect* GetCenterMargin(int x, int y, int w, int h);
    SDL_Rect* GetCenterMargin(int w, int h);

    /**
     * @brief A clip of a texture.
     * 
     */
    class Clip {
    public:
        SDL_Texture* texture;
        SDL_Rect *clip_region, *dest_region;
        double degree = 0;
        SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;

        Clip(SDL_Texture* texture = nullptr, SDL_Rect* clip_region = nullptr, SDL_Rect* dest_region = nullptr,
             double degree = 0, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

        /**
         * @brief Draws the clip(texture)
         * @note (x, y) can be in any quadrant, since as a sprite comes out from border its coord can be negative.
         * @param x X coord
         * @param y Y coord
         */
        void Draw(int x, int y);

        /**
         * @brief Replaces dimension constants (defined at windows.hpp)
         * Wraps static version of this function, transforming `dest_region` of `texture` given `clip_region`
         * 
         */
        void ReplaceUniqueDimension();
        /**
         * @brief Replaces dimension constants (defined at windows.hpp)
         * 
         * @param texture Texture given
         * @param rect Dest region/rect to be transformed
         * @param clip Clip of the texture (optional, default=nullptr)
         */
        static void ReplaceUniqueDimension(SDL_Texture* texture, SDL_Rect* rect, SDL_Rect* clip = nullptr);

        /**
         * @brief Joins multiple clips together and make an overall clip.
         * @warning ONLY use this function when no other threads are using muser::windows::renderer!
         * @note Considering that there might be multiple calls to this, windows::ResetRenderTarget() should be called after all calls, not in every call.
         * 
         * @param clips the pointer to the pointer to the beggining clip (Array of Clip*)
         * @param size Size of clips
         * @param texture_size target texture size
         * @return Clip created
         */
        static Clip FromClips(Clip* clips, std::size_t size, SDL_Rect* texture_size);

        static Clip FromClips(std::list<Clip> clips, SDL_Rect* texture_size);
    };
}  // namespace muser::sprite

#endif