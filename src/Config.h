//
// Created by jgravier on 23/01/2023.
//

#pragma once

#include <cstdint>
#include <raylib.h>

class Config {
public:
    constexpr static const Vector2 windowSize = {800, 600};
    constexpr static const uint8_t maxFPS = 60;
};