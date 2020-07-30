#include <iostream>
#include <string>

#include "SDL.h"
#include "logger.hpp"
#include "preference.hpp"
#include "resource.hpp"
#include "resource_manager.hpp"
#include "util.hpp"
#include "windows.hpp"

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }

    muser::logger::init_logger();
    muser::logger::logger->info("You are running MuserSDL v{0}", MUSER_VERSION);

    muser::windows::CreateMuserWindow();
    muser::windows::CreateMuserRenderer();

    muser::resource::InitResources();
    muser::resource::LoadBMPs();
    muser::resource::LoadResourcesToTempFiles();

    muser::preference::InitPreferences();

    constexpr muser::windows::CenteredMarginS<160, 32> TextureDim;
    muser::logger::logger->warn("{}, {}", TextureDim.x, TextureDim.y);

    auto texture = muser::windows::UploadToTexture(muser::resource::GetSurface("muser_resources.bmp"));
    SDL_SetTextureColorMod(texture, 64, 64, 64);

    SDL_Event e;
    bool quit = false;
    auto quit_key = muser::preference::GetBasicControl("quit");
    int alpha_r = 0, alpha_g = 0, alpha_b = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                muser::logger::logger->debug("User requested a quit.");
            } else if (e.type == SDL_KEYDOWN) {
                muser::logger::logger->info("User pressed '{}'", SDL_GetKeyName(e.key.keysym.sym));
                if (e.key.keysym.sym == quit_key) {
                    quit = true;
                    muser::logger::logger->debug("User pressed {} to quit.", SDL_GetKeyName(quit_key));
                }
            }
        }
        SDL_RenderClear(muser::windows::renderer);
        if (alpha_r < 255) {
            alpha_r += 16;
        } else if (alpha_g < 255) {
            alpha_g += 16;
        } else if (alpha_b < 255) {
            alpha_b += 16;
        }
        alpha_r = muser::util::constrain(alpha_r, 0, 255);
        alpha_g = muser::util::constrain(alpha_g, 0, 255);
        alpha_b = muser::util::constrain(alpha_b, 0, 255);
        SDL_SetTextureColorMod(texture, alpha_r, alpha_g, alpha_b);
        muser::windows::RenderTexture(texture, TextureDim.x, TextureDim.y, 160, 32, new SDL_Rect{0, 64, 80, 16});
        SDL_RenderPresent(muser::windows::renderer);
        SDL_Delay(50);
    }

    muser::preference::SavePreferences();
    muser::resource::ReleaseTempResources();
    SDL_Quit();
    return 0;
}