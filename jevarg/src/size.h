//
// Created by jgravier on 29/01/2023.
//

#pragma once

namespace jevarg {
    template<class T>
    class size {
    public:
        size(T width, T height) : width(width), height(height) {};
        explicit size(T n) : size(n, n) {};

        T width;
        T height;
    };
}