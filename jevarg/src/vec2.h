//
// Created by jgravier on 29/01/2023.
//

#pragma once

namespace jevarg {
    template<class T>
    class vec2 {
    public:
        vec2(T x, T y) : x(x), y(y) {};
        explicit vec2(T n) : vec2(n, n) {};

        T x;
        T y;
    };
}