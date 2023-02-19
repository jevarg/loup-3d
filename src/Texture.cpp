//
// Created by Jean on 2/18/2023.
//

#include <iostream>
#include "Texture.h"

Texture::Texture(SDL_Surface *s) : mNativeTexture(s) {
//                                     mFormat(SDL_PixelFormatEnum::SDL_PIXELFORMAT_UNKNOWN),
//                                     mSize(0) {
//    int r = SDL_QueryTexture(tex,
//                     reinterpret_cast<Uint32 *>(&mFormat),
//                     nullptr,
//                     &mSize.width,
//                     &mSize.height);
//
//    if (r) {
//        std::cerr << "Error: " << SDL_GetError() << std::endl;
//    }
}

SDL_Surface *Texture::getNativeTexture() const {
    return mNativeTexture;
}

//const jevarg::size<int> &Texture::getSize() const {
//    return mSize;
//}
