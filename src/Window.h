//
// Created by jgravier on 23/01/2023.
//

#pragma once

#include "InputManager.h"
#include "Renderer.h"
#include <memory>
#include <SDL2/SDL.h>

class Window {
public:
    explicit Window();

    ~Window();

    void update();

    void present() const;

    void clear() const;

    bool shouldClose() const;

    const Renderer &getRenderer() const;

    const InputManager &getInputManager() const;

private:
    bool mShouldClose;
    SDL_Window *mNativeWindow;
    std::shared_ptr<Renderer> mRenderer;
    InputManager mInputManager;
};
