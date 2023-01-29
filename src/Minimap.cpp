//
// Created by Jean on 1/29/2023.
//

#include "Minimap.h"
#include <cmath>
#include <raylib.h>

Minimap::Minimap(const Player &player, const Map &map) : mPlayer(player), mMap(map) {}

void Minimap::render() const {
    const std::vector<char> mapData = mMap.getData();

    for (int i = 0; i < mapData.size(); i++) {
        Color color;
        switch (mapData[i]) {
            case '1':
                color = BLUE;
                break;
            default:
                continue;
                color = GRAY;
                break;
        }

        int x = (i % mMap.getWidth()) * mMap.getCellWidth();
        int y = (i / mMap.getHeight()) * mMap.getCellHeight();

        DrawRectangle(x, y,mMap.getCellWidth(), mMap.getCellHeight(), color);
    }

    Vector2 playerPos = mPlayer.getPosition();
    Vector2 playerDir = mPlayer.getDirection();
    float angle = std::atan2(playerDir.y, playerDir.x) * RAD2DEG;
    Rectangle r = {playerPos.x, playerPos.y, 10, 10};

    DrawRectanglePro(r, {r.width / 2, r.height / 2}, angle, RED);
}
