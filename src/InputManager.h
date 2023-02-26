//
// Created by Jean on 2/16/2023.
//

#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <jevarg.h>

class InputManager {
public:
    explicit InputManager();

    void update();

    bool isKeyPressed(SDL_Scancode code) const;

    bool isModPressed(SDL_Keymod mod) const;

    bool isMousePressed(int button) const;

    const jevarg::vec2<float> &getMouseDelta() const;

private:
    const std::uint8_t *mKbdState;
    SDL_Keymod mKbdModState;
    jevarg::vec2<float> mMouseDelta;
    std::uint32_t mMouseButtonState;
};
