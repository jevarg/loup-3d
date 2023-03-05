//
// Created by jgravier on 23/01/2023.
//

#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include "Window.h"
#include "Config.h"


Window::Window() : mShouldClose(false),
                   mNativeWindow(SDL_CreateWindow("Loup 3D",
                                                  SDL_WINDOWPOS_UNDEFINED,
                                                  SDL_WINDOWPOS_UNDEFINED,
                                                  Config::windowSize.width,
                                                  Config::windowSize.height,
                                                  0)),
                   mRenderer(mNativeWindow),
                   mFrameBuffer(Config::windowSize) {
    if (mNativeWindow == nullptr) {
        std::cerr << "FATAL ERROR: " << SDL_GetError() << std::endl;
        std::exit(-1);
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_Texture *tex = SDL_CreateTexture(mRenderer.getNativeRenderer(),
                                         SDL_PIXELFORMAT_ABGR8888,
                                         SDL_TEXTUREACCESS_STREAMING,
                                         Config::windowSize.width,
                                         Config::windowSize.height);
    if (tex == nullptr) {
        std::cerr << "FATAL ERROR: " << SDL_GetError() << std::endl;
        std::exit(-1);
    }

    mVideoMemory = std::make_unique<Texture>(tex, Config::windowSize, true);
}

Window::~Window() {
    SDL_DestroyTexture(mVideoMemory->getNativeTexture());
    SDL_DestroyWindow(mNativeWindow);
}

bool Window::shouldClose() const {
    return mShouldClose;
}

void Window::clear() {
    mRenderer.clear();
    mFrameBuffer.fill({0, 0, 0, 255});
}

void Window::update() {
    mInputManager.update();

    if (mInputManager.isKeyPressed(SDL_SCANCODE_ESCAPE))
        mShouldClose = true;
}

void Window::swapBuffers() {
    mVideoMemory->lock();
    mVideoMemory->copyBuffer(mFrameBuffer.getData());
    mVideoMemory->unlock();

    mRenderer.renderTexture(*mVideoMemory);
}

void Window::present() const {
    mRenderer.present();
}

FrameBuffer &Window::getFrameBuffer() {
    return mFrameBuffer;
}

const Renderer &Window::getRenderer() const {
    return mRenderer;
}

const InputManager &Window::getInputManager() const {
    return mInputManager;
}
