/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <iostream>

#include "SDL.h"
#include "logger.hpp"
#include "resource_manager.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }
    muser::logger::init_logger();
    muser::logger::logger.info("You are running MuserSDL v{0}", MUSER_VERSION);
    muser::logger::logger.info("Resource path is: {0}", muser::resource::ResourceManager::getResourcePath());

    SDL_Quit();
    return 0;
}