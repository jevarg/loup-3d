//
// Created by Jean on 1/29/2023.
//

#pragma once

#include "Player.h"
#include "Map.h"

class Minimap {
public:
    explicit Minimap(const Player &player, const Map &map);
    void render() const;

private:
    const Player &mPlayer;
    const Map &mMap;
};
