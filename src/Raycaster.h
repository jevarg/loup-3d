//
// Created by Jean on 1/27/2023.
//

#pragma once

#include "Player.h"
#include "Map.h"
#include "Minimap.h"
#include "ResourceManager.h"
#include "Config.h"
#include <vector>
#include <jevarg.h>
#include <SDL2/SDL.h>

struct HitPoint {
    jevarg::vec2<float> point;
    float dist;
};

class Raycaster {
public:
    explicit Raycaster(const Map &map, const Player &player, const Minimap &minimap, Texture *renderTexture);

    void render(const Renderer &renderer, const ResourceManager &resourceMgr);

private:
    void mRenderWalls(const Renderer &renderer, const ResourceManager &resourceMgr);

    void mRenderFloor(const Renderer &renderer, const ResourceManager &resourceMgr);

    const Map &mMap;
    const Player &mPlayer;
    const Minimap &mMinimap;
    std::vector<std::uint8_t> mBuffer;
    Texture *mRenderTexture;
};
