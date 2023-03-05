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

void Player::setPosition(const jevarg::vec3<float> &pos) {
    mPosition = pos;
}

void Player::render() const {}

void Player::update(const InputManager &input) {
    float movementSpeed = Config::movementSpeed;
    if (input.isModPressed(KMOD_CTRL)) {
        movementSpeed *= 1.5;
    }

    if (input.isKeyPressed(SDL_SCANCODE_W)) {
        mPosition.x += mDirection.x * movementSpeed;
        mPosition.y += mDirection.y * movementSpeed;
    }

    if (input.isKeyPressed(SDL_SCANCODE_S)) {
        mPosition.x -= mDirection.x * movementSpeed;
        mPosition.y -= mDirection.y * movementSpeed;
    }

    if (input.isKeyPressed(SDL_SCANCODE_A)) {
        mPosition.x += mDirection.y * movementSpeed;
        mPosition.y -= mDirection.x * movementSpeed;
    }

    if (input.isKeyPressed(SDL_SCANCODE_D)) {
        mPosition.x -= mDirection.y * movementSpeed;
        mPosition.y += mDirection.x * movementSpeed;
    }


    const jevarg::vec2 mouseDelta = input.getMouseDelta();
//    float angle = ;
    mDirection.rotate(mouseDelta.x);
//    mDirection = {
//            mDirection.x * std::cos(angle) - mDirection.y * std::sin(angle),
//            mDirection.x * std::sin(angle) + mDirection.y * std::cos(angle)
//    };
}

const jevarg::vec3<float> &Player::getPosition() const {
    return mPosition;
}

const jevarg::vec2<float> &Player::getDirection() const {
    return mDirection;
}
