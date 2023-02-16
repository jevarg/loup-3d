//
// Created by Jean on 2/16/2023.
//

#include "InputManager.h"

void InputManager::update() {
    SDL_Event e;
    while (SDL_PollEvent(&e) > 0) {
//        switch (e.type) {
//            case SDL_QUIT:
////                mShouldClose = true;
//                break;
////            case SDL_KEYDOWN:
//                if (e.key.keysym.sym == SDLK_ESCAPE)
////                    mShouldClose = true;
//                break;
//        }
    }
}

InputManager::InputManager() : mKbdState(SDL_GetKeyboardState(nullptr)) {}

bool InputManager::operator[](SDL_Scancode code) const {
    return mKbdState[code] == 1;
}
