//
// Created by jgravier on 23/01/2023.
//

#include <cmath>
#include "Config.h"
#include "Player.h"

void Player::setPosition(Vector2 pos) {
    mPosition = pos;
}

void Player::render() const {}

void Player::update() {
    if (IsKeyDown(KEY_W)) {
        mPosition.x += mDirection.x;
        mPosition.y += mDirection.y;
    }

    if (IsKeyDown(KEY_S)) {
        mPosition.x -= mDirection.x;
        mPosition.y -= mDirection.y;
    }

    if (IsKeyDown(KEY_A)) {
        mPosition.x += mDirection.y;
        mPosition.y -= mDirection.x;
    }

    if (IsKeyDown(KEY_D)) {
        mPosition.x -= mDirection.y;
        mPosition.y += mDirection.x;
    }

    float angle;
    bool didRotate = false;
    if (IsKeyDown(KEY_RIGHT)) {
        angle = Config::rotationSpeed * DEG2RAD;
        didRotate = true;
    }

    if (IsKeyDown(KEY_LEFT)) {
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

const Vector2 &Player::getPosition() const {
    return mPosition;
}

const Vector2 &Player::getDirection() const {
    return mDirection;
}

const Vector2 &Player::getPlane() const {
    return mPlane;
}

const Vector2 &Player::getDeltaPosition() const {
    return mDeltaPosition;
}
