//
// Created by Jean on 2/18/2023.
//

#pragma once

#include <SDL2/SDL_render.h>
#include <jevarg.h>
#include <cstdint>

class Texture {
public:
    explicit Texture(SDL_Texture *texture, const jevarg::size<int> &s, bool writable);

    const jevarg::size<int> &getSize() const;

    bool isWritable() const;

    bool isLocked() const;

    SDL_Texture *getNativeTexture() const;

    void lock();

    void unlock();

    void fill(std::uint8_t n);

    void copyBuffer(const std::uint8_t *buf);

private:
    SDL_Texture *mNativeTexture;
    jevarg::size<int> mSize;
    bool mWritable;
    bool mLocked;

    void *mPixels;
    int mPitch;

};
