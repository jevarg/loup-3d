//
// Created by Jean on 2/25/2023.
//

#pragma once

#include <cstdint>

namespace jevarg {
    struct color {
        static constexpr color white() { return {255, 255, 255, 255}; };

        static constexpr color black() { return {0, 0, 0, 255}; };

        static constexpr color yellow() { return {255, 255, 0, 255}; };

        static constexpr color blue() { return {0x60, 0xa3, 0xd9, 0xff}; };

        static constexpr color green() { return {0x59, 0x98, 0x1A, 0xff}; };

        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;
        std::uint8_t a;
    };
}