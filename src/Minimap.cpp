//
// Created by Jean on 1/29/2023.
//

#include "Minimap.h"
#include "Config.h"
#include <cmath>
#include <raylib.h>

Minimap::Minimap(const Player &player, const Map &map) : mPlayer(player), mMap(map),
                                                         cellSize(map.getWidth() * Config::mapScale,
                                                                  map.getHeight() * Config::mapScale) {}

void Minimap::render() const {
    const std::vector<char> mapData = mMap.getData();

    for (int i = 0; i < mapData.size(); i++) {
        Color color;
        switch (mapData[i]) {
            case '1':
                color = BLUE;
                break;
            default:
                color = GRAY;
                break;
        }

        int x = (i % mMap.getWidth()) * cellSize.width;
        int y = (i / mMap.getWidth()) * cellSize.height;

        DrawRectangle(x, y, cellSize.width, cellSize.height, color);
    }

    Vector2 playerPos = mPlayer.getPosition();
    Vector2 playerDir = mPlayer.getDirection();
    float angle = std::atan2(playerDir.y, playerDir.x) * RAD2DEG;
    Rectangle r = {playerPos.x * cellSize.width, playerPos.y * cellSize.height, 10, 10};

    DrawRectanglePro(r, {r.width / 2, r.height / 2}, angle, RED);
    DrawLine(playerPos.x * cellSize.width, playerPos.y * cellSize.height, playerPos.x * cellSize.width + playerDir.x * 100, playerPos.y * cellSize.height + playerDir.y * 100, GREEN);
}

void Minimap::drawPlayerFOVLine(const Vector2 &hitPoint) const {
    const Vector2 &playerPos = mPlayer.getPosition();

    DrawLine(playerPos.x * cellSize.width, playerPos.y * cellSize.height,
             hitPoint.x * cellSize.width, hitPoint.y * cellSize.height, YELLOW);
}
