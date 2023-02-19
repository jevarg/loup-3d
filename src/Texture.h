//
// Created by Jean on 2/18/2023.
//

#pragma once

#include <SDL2/SDL.h>
#include <jevarg.h>

class Texture {
public:
    explicit Texture(SDL_Surface *s);
    SDL_Surface *getNativeTexture() const;
//    const jevarg::size<int> &getSize() const;

private:
    SDL_Surface *mNativeTexture;
//    SDL_PixelFormatEnum mFormat;
//    jevarg::size<int> mSize;
};
