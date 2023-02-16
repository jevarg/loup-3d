//
// Created by jgravier on 23/01/2023.
//

#include "Window.h"
#include "Config.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>

#define SDL_TRY(x) { \
    int _RET_CODE = x;                                          \
    if (_RET_CODE) {                                            \
        std::cerr << "FATAL ERROR: " << SDL_GetError() << std::endl;  \
        std::exit(_RET_CODE);                                   \
    }                                                           \
}

Window::Window() : mShouldClose(false) {
    SDL_TRY(SDL_Init(SDL_INIT_VIDEO))
    mNativeWindow = SDL_CreateWindow("Loup 3D",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     Config::windowSize.width,
                                     Config::windowSize.height,
                                     0);

    if (mNativeWindow == nullptr) {
        std::cerr << "FATAL ERROR: " << SDL_GetError() << std::endl;
        std::exit(-1);
    }

    mRenderer = SDL_CreateRenderer(mNativeWindow, 0, 0);
    if (mRenderer == nullptr) {
        std::cerr << "FATAL ERROR: " << SDL_GetError() << std::endl;
        std::exit(-1);
    }

//    SDL_SetRelativeMouseMode(SDL_TRUE);
}

Window::~Window() {
    SDL_Quit();
//    CloseWindow();
}

bool Window::shouldClose() const {
    return mShouldClose;
}

void Window::clear() const {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
}

void Window::update() {
    mInputManager.update();

    if (mInputManager[SDL_SCANCODE_ESCAPE])
        mShouldClose = true;
}

void Window::present() const {
    SDL_RenderPresent(mRenderer);
}

SDL_Renderer *Window::getRenderer() const {
    return mRenderer;
}

const InputManager &Window::getInputManager() const {
    return mInputManager;
}


