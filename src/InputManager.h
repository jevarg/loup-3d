//
// Created by Jean on 2/16/2023.
//

#pragma once

#include <SDL2/SDL.h>
#include <cstdint>

class InputManager {
public:
    explicit InputManager();
    void update();

    bool operator[](SDL_Scancode code) const;

private:
    const std::uint8_t *mKbdState;
};
