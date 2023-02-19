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
    explicit Raycaster(const Map &map, const Player &player, const Minimap &minimap, Texture *renderTexture);

    void render(const Renderer &renderer, const ResourceManager &resourceMgr) const;

private:
    void mRenderWalls(const Renderer &renderer, const ResourceManager &resourceMgr) const;

    void mRenderFloor(const Renderer &renderer, const ResourceManager &resourceMgr) const;

    const Map &mMap;
    const Player &mPlayer;
    const Minimap &mMinimap;
    Texture *mRenderTexture;
};
