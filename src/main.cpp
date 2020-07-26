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

    auto texture = muser::windows::UploadToTexture(muser::resource::GetSurface("muser_resources.bmp"));
    SDL_RenderClear(muser::windows::renderer);
    muser::windows::RenderTexture(texture, 0, 0, new SDL_Rect{0, 0, 16, 16});
    SDL_RenderPresent(muser::windows::renderer);

    SDL_Event e;
    bool quit = false;
    auto quit_key = muser::preference::GetBasicControl("quit");
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
    }

    muser::preference::SavePreferences();
    muser::resource::ReleaseTempResources();
    SDL_Quit();
    return 0;
}