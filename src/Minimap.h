//
// Created by Jean on 1/29/2023.
//

#pragma once

#include <jevarg.h>
#include "Player.h"
#include "Map.h"
#include "FrameBuffer.h"

struct HitPoint;

class Minimap {
public:
    explicit Minimap(const Player &player, const Map &map);

    void render(FrameBuffer &frameBuffer) const;

    void drawPlayerFOV(FrameBuffer &frameBuffer, const std::vector<HitPoint> &hitPoints) const;

    const jevarg::size<int> &getCellSize() const;

private:
    const Player &mPlayer;
    const Map &mMap;

    jevarg::size<int> mCellSize;
};
