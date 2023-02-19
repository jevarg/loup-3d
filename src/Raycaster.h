//
// Created by Jean on 1/27/2023.
//

#pragma once

#include "Player.h"
#include "Map.h"
#include "Minimap.h"
#include "ResourceManager.h"
#include <jevarg.h>
#include <SDL2/SDL.h>

struct HitPoint {
    jevarg::vec2<float> point;
    float dist;
};

class Raycaster {
public:
    explicit Raycaster(const Map &map, const Player &player, const Minimap &minimap);
    void render(SDL_Renderer *renderer, const ResourceManager &resourceMgr) const;

private:
    void mRenderWalls(SDL_Renderer *renderer, const ResourceManager &resourceMgr) const;
    void mRenderFloor(SDL_Renderer *renderer, const ResourceManager &resourceMgr) const;

    const Map &mMap;
    const Player &mPlayer;
    const Minimap &mMinimap;
//    Texture2D mFloorTex;
//    Image mFloorImg;
};
