//
// Created by Jean on 2/19/2023.
//

#include "Renderer.h"
#include "Config.h"
#include <iostream>

Renderer::Renderer(SDL_Window *w) {
    mNativeRenderer = SDL_CreateRenderer(w, 0, SDL_RENDERER_ACCELERATED);
    if (mNativeRenderer == nullptr) {
        std::cerr << "FATAL ERROR: " << SDL_GetError() << std::endl;
        std::exit(-1);
    }

    mStreamedTexture = SDL_CreateTexture(mNativeRenderer, SDL_PixelFormatEnum::SDL_PIXELFORMAT_RGBA8888,
                                         SDL_TEXTUREACCESS_STREAMING, Config::windowSize.width,
                                         Config::windowSize.height);
    if (mStreamedTexture == nullptr) {
        std::cerr << "FATAL ERROR: " << SDL_GetError() << std::endl;
        std::exit(-1);
    }
}

Renderer::~Renderer() {
    SDL_DestroyTexture(mStreamedTexture);
    SDL_DestroyRenderer(mNativeRenderer);
}

//void Renderer::copyPixels(void *raw) const {
//    void *texData;
//    int rawPitch;
//
//    SDL_LockTexture(mStreamedTexture, nullptr, &texData, &rawPitch);
//    std::memcpy(texData, raw, rawPitch * Config::windowSize.height);
//    SDL_UnlockTexture(mStreamedTexture);
//}

void Renderer::clear() const {
    SDL_SetRenderDrawColor(mNativeRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mNativeRenderer);
}

void Renderer::present() const {
    SDL_RenderPresent(mNativeRenderer);
}

Texture *Renderer::createTexture(const jevarg::size<int> &s, bool writable) const {
    SDL_TextureAccess access = writable ? SDL_TEXTUREACCESS_STREAMING : SDL_TEXTUREACCESS_STATIC;
    SDL_Texture *tex = SDL_CreateTexture(mNativeRenderer,
                                         SDL_PIXELFORMAT_RGBA8888,
                                         access,
                                         s.width,
                                         s.height);
    if (tex == nullptr) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return new Texture(tex, s, writable);
}

void Renderer::renderTexture(const Texture &texture) const {
    SDL_Rect rect{0, 0, Config::windowSize.width, Config::windowSize.height};
    SDL_RenderCopy(mNativeRenderer, texture.getNativeTexture(), &rect, &rect);
}

SDL_Renderer *Renderer::getMNativeRenderer() const {
    return mNativeRenderer;
}
