//
// Created by Jean on 2/15/2023.
//

#pragma once

namespace jevarg {
    template<class T>
    class vec3 {
    public:
        vec3(T x, T y, T z) : x(x), y(y), z(z) {};
        vec3(const vec3<T> &v) : vec3(v.x, v.y, v.z) {};
        explicit vec3(T n) : vec3(n, n, n) {};

        template<class U> explicit operator vec3<U>() const {
            return vec3<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
        };

        T x;
        T y;
        T z;
    };
}