/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "SDL.h"
#include <stdio.h>

int main( int argc, char* args[] )
{
    printf("Hi\n");
	SDL_Init(SDL_INIT_VIDEO);
    SDL_Delay(5 * 1000);
    SDL_Quit();
    return 0;
}