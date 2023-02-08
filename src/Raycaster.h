//
// Created by Jean on 1/27/2023.
//

#pragma once

#include "Player.h"
#include "Map.h"
#include "Minimap.h"

struct HitPoint {
    Vector2 point;
    float dist;
};

class Raycaster {
public:
    explicit Raycaster(const Map &map, const Player &player, const Minimap &minimap);
    void render(const Texture2D &wallTex) const;

private:
    void mRenderWalls(const Texture2D &wallTex) const;
    void mRenderFloor() const;

    const Map &mMap;
    const Player &mPlayer;
    const Minimap &mMinimap;
    Texture2D mFloorTex;
    Image mFloorImg;
};
