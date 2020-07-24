#include <iostream>
#include <string>

#include "SDL.h"
#include "logger.hpp"
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
    muser::resource::LoadResourcesToTempFiles();

    auto texture = muser::windows::UploadToTexture(muser::windows::LoadBMP(muser::resource::GetTempFile("muser_resources.bmp")));
    SDL_RenderClear(muser::windows::renderer);
    SDL_RenderCopy(muser::windows::renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(muser::windows::renderer);

    SDL_Delay(5000);

    muser::resource::ReleaseTempResources();
    SDL_Quit();
    return 0;
}