//
// Created by jgravier on 23/01/2023.
//

#include <cmath>
#include "Player.h"

void Player::setPosition(Vector2 pos) {
    m_position = pos;
}

void Player::render() const {
    Rectangle r = {m_position.x, m_position.y, 10, 10};
    float angle = std::atan2(m_direction.y, m_direction.x) * RAD2DEG;
    DrawRectanglePro(r, {r.width / 2, r.height / 2}, angle, RED);
    DrawLineV(m_position, {
        m_position.x + m_direction.x * 100,
        m_position.y + m_direction.y * 100
    }, YELLOW);
}

void Player::update() {
    if (IsKeyDown(KEY_W)) {
        m_position.x += m_direction.x;
        m_position.y += m_direction.y;
    }

    if (IsKeyDown(KEY_S)) {
        m_position.x -= m_direction.x;
        m_position.y -= m_direction.y;
    }

    if (IsKeyDown(KEY_A)) {
        m_position.x += m_direction.y;
        m_position.y -= m_direction.x;
    }

    if (IsKeyDown(KEY_D)) {
        m_position.x -= m_direction.y;
        m_position.y += m_direction.x;
    }

    if (IsKeyDown(KEY_RIGHT)) {

    }

    Vector2 mousePos = GetMousePosition();
    Vector2 dir = {
            .x = mousePos.x - m_position.x,
            .y = mousePos.y - m_position.y
    };

    float magnitude = std::sqrtf(std::powf(dir.x, 2) + std::powf(dir.y, 2));
    m_direction = {
            .x = dir.x / magnitude,
            .y = dir.y / magnitude
    };
}
