//
// Created by jgravier on 29/01/2023.
//

#pragma once

#include <cmath>
#include "size.h"

namespace jevarg {
    template<class T>
    struct vec2 {
    public:
        constexpr vec2(T x, T y) : x(x), y(y) {};

        explicit vec2(T n) : vec2(n, n) {};

        template<class U>
        explicit operator vec2<U>() {
            return vec2<U>(static_cast<U>(x), static_cast<U>(y));
        };

        template<class U>
        vec2<T> operator+(const jevarg::size<U> &size) const {
            return {
                    x + size.width,
                    y + size.height
            };
        }

        template<class U>
        vec2<T> operator*(const jevarg::size<U> &size) const {
            return {
                    x * size.width,
                    y * size.height
            };
        }

        vec2<float> normalized() const {
            float l = length();
            return {
                    x / l,
                    y / l
            };
        }

        void rotate(float angle, const vec2<T> &origin = {0, 0}) {
            x -= origin.x;
            y -= origin.y;

            float cosAngle = std::cos(angle);
            float sinAngle = std::sin(angle);

            T newX = (x * cosAngle - y * sinAngle) + origin.x;
            T newY = (x * sinAngle + y * cosAngle) + origin.y;

            x = newX;
            y = newY;
        };

        float length() const {
            return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
        };

        T x;
        T y;
    };
}