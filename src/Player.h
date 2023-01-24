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
private:
    Vector2 m_position;
    Vector2 m_direction;
};
