//
// Created by jgravier on 23/01/2023.
//

#include "Config.h"
#include "Player.h"

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

    if (input.isKeyPressed(SDL_SCANCODE_SPACE)) {
        mPosition.z += 1.0f;
    }

    const jevarg::vec2 mouseDelta = input.getMouseDelta();
    mDirection.rotate(mouseDelta.x);
}

const jevarg::vec3<float> &Player::getPosition() const {
    return mPosition;
}

const jevarg::vec2<float> &Player::getDirection() const {
    return mDirection;
}
