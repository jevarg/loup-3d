//
// Created by jgravier on 29/01/2023.
//

#pragma once

namespace jevarg {
    template<class T>
    class size {
    public:
        constexpr size(T width, T height) : width(width), height(height) {};
        explicit size(T n) : size(n, n) {};

        template<class U> explicit operator size<U>() {
            return size<U>{static_cast<U>(width),
                           static_cast<U>(height)};
        };

        template<class U> size<T> operator* (U n) const {
            return size<T>{static_cast<T>(width * n),
                           static_cast<T>(height * n)};
        }

        T width;
        T height;
    };
}