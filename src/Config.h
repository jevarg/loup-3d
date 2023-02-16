//
// Created by jgravier on 23/01/2023.
//

#pragma once

#include <cstdint>
#include <jevarg.h>

class Config {
public:
    constexpr static const jevarg::size<int> windowSize{800, 600};
    constexpr static const uint8_t maxFPS = 60;
    constexpr static const float fieldOfView = 70.0f;
    constexpr static const float mapScale = 1.0f;
    constexpr static const float rotationSpeed = 1.5f;
    constexpr static const bool distantShadows = true;
    constexpr static const uint8_t maxShadow = 255;
    constexpr static const float movementSpeed = 0.03f;
};