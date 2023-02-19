//
// Created by jgravier on 23/01/2023.
//

#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include "Window.h"
#include "Config.h"


Window::Window() : mShouldClose(false) {
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

    mRenderer = std::make_shared<Renderer>(mNativeWindow);
//    SDL_SetRelativeMouseMode(SDL_TRUE);
}

Window::~Window() {
    SDL_DestroyWindow(mNativeWindow);
}

bool Window::shouldClose() const {
    return mShouldClose;
}

void Window::clear() const {
    mRenderer->clear();
}

void Window::update() {
    mInputManager.update();

    if (mInputManager[SDL_SCANCODE_ESCAPE])
        mShouldClose = true;
}

void Window::present() const {
    mRenderer->present();
}

const Renderer &Window::getRenderer() const {
    return *mRenderer;
}

const InputManager &Window::getInputManager() const {
    return mInputManager;
}


