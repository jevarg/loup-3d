//
// Created by Jean on 1/29/2023.
//

#pragma once

#include <jevarg.h>
#include "Player.h"
#include "Map.h"

class Minimap {
public:
    explicit Minimap(const Player &player, const Map &map);
    void render() const;
    void drawPlayerFOVLine(const Vector2 &hitPoint) const;

private:
    const Player &mPlayer;
    const Map &mMap;

    jevarg::size<int> cellSize;
};
