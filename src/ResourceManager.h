//
// Created by Jean on 2/18/2023.
//

#pragma once

#include <memory>
#include <unordered_map>
#include <SDL2/SDL_render.h>
#include "Texture.h"

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
    void loadResources(SDL_Renderer *);
    std::shared_ptr<void> operator [](ResourceID id) const;
    std::shared_ptr<Texture> getTexture(ResourceID id) const;

private:
    void mLoadResource(SDL_Renderer *renderer, const char *path, ResourceID id);
    std::unordered_map<ResourceID, std::shared_ptr<Texture>> mTextures;
//    std::unordered_map<ResourceID, void *> mTextures;
};