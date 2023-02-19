//
// Created by jgravier on 23/01/2023.
//

#include <iostream>
#include <SDL2/SDL_image.h>
#include "Game.h"

#define TRY_OR_FAIL(x, expected, msg) { \
    if (x != expected) {                                    \
        std::cerr << "Fatal error: " << msg << std::endl;    \
        return -1;                                          \
    }                                                       \
}

int main(int argc, char *argv[]) {
    TRY_OR_FAIL(SDL_Init(SDL_INIT_VIDEO), 0, SDL_GetError())
    TRY_OR_FAIL(IMG_Init(IMG_INIT_PNG), IMG_INIT_PNG, "Failed to initialize SDL_Image")

    Game game;
    game.start();

    IMG_Quit();
    SDL_Quit();

    return 0;
}