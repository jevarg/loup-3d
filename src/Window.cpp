//
// Created by jgravier on 23/01/2023.
//

#include "Window.h"
#include "Config.h"
#include <raylib.h>

Window::Window() {
    InitWindow(Config::windowSize.x, Config::windowSize.y, "Loup 3D");
    SetTargetFPS(Config::maxFPS);
}

Window::~Window() {
    CloseWindow();
}

bool Window::shouldClose() const {
    return WindowShouldClose();
}

