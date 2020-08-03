#include "sprite.hpp"
#include "windows.hpp"

namespace muser::sprite {
    SDL_Rect* GetCenterMargin(int x, int y, int w, int h) {
        return new SDL_Rect{x - w / 2, y - w / 2, w, h};
    }
    SDL_Rect* GetCenterMargin(int w, int h) {
        return GetCenterMargin(windows::kWindowCenterX, windows::kWindowCenterY, w, h);
    }

    Clip Clip::FromClips(Clip* clips, std::size_t size, SDL_Rect* texture_size) {
        Clip res;
        res.texture = SDL_CreateTexture(windows::renderer, SDL_PIXELFORMAT_RGBA8888,
                                        SDL_TEXTUREACCESS_TARGET, texture_size->w, texture_size->h);
        windows::SetRenderTarget(res.texture);
        for (std::size_t i = 0; i < size; i++) {
            windows::RenderTexture(clips[i].texture, clips[i].dest_region, clips[i].clip_region,
                                   windows::renderer, clips[i].degree, clips[i].flip);
        }
        // Call this after all calls of FromClips or FromClip has done!
        // >>> windows::ResetRenderTarget();
        res.clip_region = texture_size;
        // Default - No scaling
        res.dest_region = res.clip_region;
        return res;
    }

    /**
     * @brief Set x and y of dest_region to argument x and y, and use windows::RenderTexture to render
     * @note In this function, dest_region->x and dest_region_y are used as a buffer, \
     * so we don't have to allocate a new SDL_Rect*, \
     * which means if directly use windows::RenderTexture from somewhere else, the coord will be that of the last drawn.
     * 
     * @param x X coord to be drawn at
     * @param y Y coord to be drawn at
     */
    void Clip::Draw(int x, int y) {
        dest_region->x = x;
        dest_region->y = y;
        windows::RenderTexture(texture, dest_region, clip_region, windows::renderer, degree, flip);
    }

    void Clip::ReplaceUniqueDimension(SDL_Texture* texture, SDL_Rect* rect, SDL_Rect* clip) {
        rect->w = rect->w == STRETCH_SCREEN_SIZE ? windows::kWindowWidth : rect->w;
        rect->h = rect->h == STRETCH_SCREEN_SIZE ? windows::kWindowHeight : rect->h;
        if (clip != nullptr) {
            rect->w = rect->w == TEXTURE_SIZE ? clip->w : rect->w;
            rect->h = rect->h == TEXTURE_SIZE ? clip->h : rect->h;
        } else {
            SDL_QueryTexture(texture, nullptr, nullptr,
                             rect->w == TEXTURE_SIZE ? &rect->w : nullptr, rect->h == TEXTURE_SIZE ? &rect->h : nullptr);
        }
    }

    void Clip::ReplaceUniqueDimension() {
        ReplaceUniqueDimension(texture, dest_region, clip_region);
    }
}  // namespace muser::sprite
