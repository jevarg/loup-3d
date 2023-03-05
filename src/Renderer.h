//
// Created by Jean on 2/19/2023.
//

#pragma once

#include <SDL2/SDL_render.h>
#include <memory>
#include "Texture.h"

class Renderer {
public:
    explicit Renderer(SDL_Window *w);

    ~Renderer();

    void clear() const;

    void present() const;

    SDL_Renderer *getNativeRenderer();

//    Texture *createTexture(const jevarg::size<int> &size, bool writable = false) const;

    void renderTexture(const Texture &texture) const;

private:
    SDL_Renderer *mNativeRenderer;
//    SDL_Texture *mStreamedTexture;
};
