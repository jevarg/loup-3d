//
// Created by jgravier on 23/01/2023.
//

#pragma once

#include <jevarg.h>
#include "InputManager.h"

class Player {
public:
    void setPosition(jevarg::vec3<float> pos);
    void update(const InputManager &input);
    void render() const;

    const jevarg::vec3<float> &getPosition() const;
    const jevarg::vec2<float> &getDirection() const;

private:
    jevarg::vec3<float> mPosition{0};
    jevarg::vec2<float> mDirection{0, 1};
};
