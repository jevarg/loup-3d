//
// Created by jgravier on 23/01/2023.
//

#pragma once

#include "InputManager.h"
#include "Renderer.h"
#include "FrameBuffer.h"
#include <memory>
#include <SDL2/SDL.h>

class Window {
public:
    explicit Window();

    ~Window();

    void update();

    void swapBuffers();

    void present() const;

    void clear();

    bool shouldClose() const;

    FrameBuffer &getFrameBuffer();

    const Renderer &getRenderer() const;

    const InputManager &getInputManager() const;

private:
    bool mShouldClose;
    SDL_Window *mNativeWindow;
    InputManager mInputManager;
    FrameBuffer mFrameBuffer;
    Renderer mRenderer;
    std::unique_ptr<Texture> mVideoMemory;
};
