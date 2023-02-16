//
// Created by jgravier on 23/01/2023.
//

#include <cmath>
#include "Config.h"
#include "Player.h"

#ifndef PI
    #define PI 3.14159265358979323846f
#endif
#ifndef DEG2RAD
    #define DEG2RAD (PI/180.0f)
#endif
#ifndef RAD2DEG
    #define RAD2DEG (180.0f/PI)
#endif

void Player::setPosition(jevarg::vec3<float> pos) {
    mPosition = pos;
}

void Player::render() const {}

void Player::update(const InputManager &input) {
    if (input[SDL_SCANCODE_W]) {
        mPosition.x += mDirection.x * Config::movementSpeed;
        mPosition.y += mDirection.y * Config::movementSpeed;
    }

    if (input[SDL_SCANCODE_S]) {
        mPosition.x -= mDirection.x * Config::movementSpeed;
        mPosition.y -= mDirection.y * Config::movementSpeed;
    }

    if (input[SDL_SCANCODE_A]) {
        mPosition.x += mDirection.y * Config::movementSpeed;
        mPosition.y -= mDirection.x * Config::movementSpeed;
    }

    if (input[SDL_SCANCODE_D]) {
        mPosition.x -= mDirection.y * Config::movementSpeed;
        mPosition.y += mDirection.x * Config::movementSpeed;
    }

    float angle;
    bool didRotate = false;
    if (input[SDL_SCANCODE_RIGHT]) {
        angle = Config::rotationSpeed * DEG2RAD;
        didRotate = true;
    }

    if (input[SDL_SCANCODE_LEFT]) {
        angle = -Config::rotationSpeed * DEG2RAD;
        didRotate = true;
    }

    if (didRotate) {
        mDirection = {
                mDirection.x * std::cos(angle) - mDirection.y * std::sin(angle),
                mDirection.x * std::sin(angle) + mDirection.y * std::cos(angle)
        };
    }
}

const jevarg::vec3<float> &Player::getPosition() const {
    return mPosition;
}

const jevarg::vec2<float> &Player::getDirection() const {
    return mDirection;
}
