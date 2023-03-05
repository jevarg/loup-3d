//
// Created by Jean on 2/18/2023.
//

#include <jevarg.h>
#include <iostream>
#include "Texture.h"

Texture::Texture(SDL_Texture *texture, const jevarg::size<int> &s, bool writable) :
        mNativeTexture(texture),
        mSize(s),
        mWritable(writable),
        mLocked(false),
        mPixels(nullptr),
        mPitch(0) {
    fill(0);
}

const jevarg::size<int> &Texture::getSize() const {
    return mSize;
}

bool Texture::isWritable() const {
    return mWritable;
}

bool Texture::isLocked() const {
    return mLocked;
}

SDL_Texture *Texture::getNativeTexture() const {
    return mNativeTexture;
}


void Texture::lock() {
    if (mLocked) {
        return;
    }

    int r = SDL_LockTexture(mNativeTexture, nullptr, &mPixels, &mPitch);
    if (r) {
        std::cerr << "Could not lock texture: " << SDL_GetError() << std::endl;
        return;
    }

    mLocked = true;
}

void Texture::unlock() {
    if (!mLocked) {
        return;
    }

    SDL_UnlockTexture(mNativeTexture);

    mPixels = nullptr;
    mLocked = false;
}

void Texture::fill(std::uint8_t n) {
    lock();
    std::memset(mPixels, n, mPitch * mSize.height);
    unlock();
}


void Texture::copyBuffer(const std::uint8_t *buf) {
    if (!mLocked) {
        std::cerr << "Ignored: texture not locked" << std::endl;
        return;
    }

    std::memcpy(mPixels, buf, mPitch * mSize.height);
}
