//
// Created by jgravier on 23/01/2023.
//

#pragma once

#include <SDL2/SDL.h>
#include "InputManager.h"

class Window {
public:
    explicit Window();
    ~Window();

    void update();
    void present() const;
    void clear() const;

    bool shouldClose() const;

    SDL_Renderer *getRenderer() const;
    const InputManager &getInputManager() const;

private:
    bool mShouldClose;
    SDL_Window *mNativeWindow;
    SDL_Renderer *mRenderer;
    InputManager mInputManager;
};
