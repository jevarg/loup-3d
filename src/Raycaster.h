//
// Created by Jean on 1/27/2023.
//

#pragma once

#include "Player.h"
#include "Map.h"
#include "Minimap.h"
#include "ResourceManager.h"
#include "Config.h"
#include "FrameBuffer.h"
#include <vector>
#include <jevarg.h>
#include <SDL2/SDL.h>

struct HitPoint {
    jevarg::vec2<float> point;
    float dist;
};

class Raycaster {
public:
    explicit Raycaster(const Map &map, const Player &player, const Minimap &minimap);

    void render(FrameBuffer &frameBuffer, const ResourceManager &resourceMgr);

private:
    void mRenderWalls(FrameBuffer &frameBuffer, const ResourceManager &resourceMgr);

    void mRenderFloor(FrameBuffer &frameBuffer, const ResourceManager &resourceMgr);

    const Map &mMap;
    const Player &mPlayer;
    const Minimap &mMinimap;
//    std::vector<std::uint8_t> mBuffer;
};
