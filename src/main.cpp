#include <iostream>
#include <string>

#include "SDL.h"
#include "logger.hpp"
#include "resource.hpp"
#include "resource_manager.hpp"
#include "windows.hpp"

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }
    muser::logger::init_logger();
    muser::logger::logger.info("You are running MuserSDL v{0}", MUSER_VERSION);

    muser::windows::CreateMuserWindow();
    muser::windows::CreateMuserRenderer();

    SDL_Quit();
    return 0;
}