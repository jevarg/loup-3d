//
// Created by jgravier on 23/01/2023.
//

#pragma once

#include <raylib.h>

class Player {
public:
    void setPosition(Vector2 pos);
    void update();
    void render() const;

    const Vector2 &getPosition() const;
    const Vector2 &getDirection() const;

private:
    Vector2 mPosition{};
    Vector2 mDirection{0, 1};
};
