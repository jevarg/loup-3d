//
// Created by Jean on 2/18/2023.
//

#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>
#include "ResourceManager.h"
#include "Texture.h"

void ResourceManager::mLoadResource(SDL_Renderer *renderer, const char *path, ResourceID id) {
    if (mTextures.contains(id)) {
        std::cout << "Warning: Skipped texture with ID " << id << ": Already loaded" << std::endl;
        return;
    }

//    SDL_Texture *tex = IMG_LoadTexture(renderer, path);
    SDL_Surface *tex = IMG_Load(path);
    if (tex == nullptr) {
        std::cerr << "Error: " << IMG_GetError() << std::endl;
    }

    mTextures[id] = std::make_shared<Texture>(tex);
}

void ResourceManager::loadResources(SDL_Renderer *renderer) {
    //    mLoadResource(renderer, "missing.png", ResourceID::MISSING);
    mLoadResource(renderer, "assets/textures/wall.png", ResourceID::TEX_WALL_1);
    mLoadResource(renderer, "assets/textures/floor.png", ResourceID::TEX_FLOOR_1);
}

std::shared_ptr<void> ResourceManager::operator[](ResourceID id) const {
    return mTextures.at(id);
}

std::shared_ptr<Texture> ResourceManager::getTexture(ResourceID id) const {
    return mTextures.at(id);
}
