//
// Created by Jean on 2/18/2023.
//

#pragma once

#include <memory>
#include <unordered_map>
#include <SDL2/SDL_render.h>
#include "Texture.h"
#include "Renderer.h"

enum ResourceType {
    TEXTURE = 0
};

enum ResourceID {
    MISSING = 0,
    TEX_WALL_1,
    TEX_FLOOR_1
};

class ResourceManager {
public:
    void loadResources();

    SDL_Surface *getTexture(ResourceID id) const;

private:
    void mLoadResource(ResourceID id, const char *path);

    std::unordered_map<ResourceID, SDL_Surface *> mTextures;
};