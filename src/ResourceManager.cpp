//
// Created by Jean on 2/18/2023.
//

#include <SDL2/SDL_image.h>
#include <iostream>
#include "ResourceManager.h"

void ResourceManager::mLoadResource(ResourceID id, const char *path) {
    if (mTextures.contains(id)) {
        std::cout << "Warning: Skipped texture with ID " << id << ": Already loaded" << std::endl;
        return;
    }

    SDL_Surface *surface = IMG_Load(path);
    if (surface == nullptr) {
        std::cerr << "Error: " << IMG_GetError() << std::endl;
    }

    mTextures[id] = surface;
}

void ResourceManager::loadResources() {
    //    mLoadResource(renderer, "missing.png", ResourceID::MISSING);
    mLoadResource(ResourceID::TEX_WALL_1, "assets/textures/wall.png");
    mLoadResource(ResourceID::TEX_FLOOR_1, "assets/textures/floor.png");
}

SDL_Surface *ResourceManager::getTexture(ResourceID id) const {
    return mTextures.at(id);
}
