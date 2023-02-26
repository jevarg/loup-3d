//
// Created by Jean on 2/16/2023.
//

#include "Config.h"
#include "InputManager.h"

InputManager::InputManager() : mKbdState(SDL_GetKeyboardState(nullptr)),
                               mMouseDelta(0) {}

void InputManager::update() {
    SDL_PumpEvents();

    int rawMouseX = 0;
    int rawMouseY = 0;

    mMouseButtonState = SDL_GetRelativeMouseState(&rawMouseX, &rawMouseY);
    mMouseDelta.x = static_cast<float>(rawMouseX) / Config::windowSize.width;
    mMouseDelta.y = static_cast<float>(rawMouseY) / Config::windowSize.height;

    mKbdModState = SDL_GetModState();
}

bool InputManager::isKeyPressed(SDL_Scancode code) const {
    return mKbdState[code] == 1;
}

const jevarg::vec2<float> &InputManager::getMouseDelta() const {
    return mMouseDelta;
}

bool InputManager::isMousePressed(int button) const {
    return mMouseButtonState & SDL_BUTTON(button);
}

bool InputManager::isModPressed(SDL_Keymod mod) const {
    return mKbdModState & mod;
}
