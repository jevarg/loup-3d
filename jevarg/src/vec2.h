//
// Created by jgravier on 29/01/2023.
//

#pragma once

namespace jevarg {
    template<class T>
    class vec2 {
    public:
        constexpr vec2(T x, T y) : x(x), y(y) {};
        explicit vec2(T n) : vec2(n, n) {};

        template<class U> explicit operator vec2<U>() {
            return vec2<U>(static_cast<U>(x), static_cast<U>(y));
        };

        T x;
        T y;
    };
}