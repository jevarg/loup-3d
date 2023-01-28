//
// Created by Jean on 1/27/2023.
//

#include <raylib.h>
#include <cmath>
#include "Raycaster.h"
#include "Config.h"

Raycaster::Raycaster(const Map &map, const Player &player) : mMap(map), mPlayer(player) {}

void Raycaster::render() const {
    Vector2 dir = mPlayer.getDirection();
    Vector2 playerPos = mPlayer.getPosition();
    Vector2 pos = {
            playerPos.x / mMap.getCellWidth(),
            playerPos.y / mMap.getCellHeight()
    };

    for (int x = 0; x < static_cast<int>(Config::windowSize.x); x++) {
        float camX = 2.0f * static_cast<float>(x) / Config::windowSize.x - 1;
        Vector2 rayDir = {
                .x = dir.x - dir.y * camX,
                .y = dir.y + dir.x * camX
        };

        uint8_t cellX = static_cast<int>(pos.x);
        uint8_t cellY = static_cast<int>(pos.y);

        float deltaX = std::abs(1 / rayDir.x);
        float deltaY = std::abs(1 / rayDir.y);

        float sideDistX;
        float sideDistY;

        int stepX;
        int stepY;
        if (rayDir.x < 0) { // WEST
            stepX = -1;
            sideDistX = (pos.x - cellX) * deltaX;
        } else { // EAST
            stepX = 1;
            sideDistX = (cellX + 1 - pos.x) * deltaX;
        }

        if (rayDir.y < 0) { // NORTH
            stepY = -1;
            sideDistY = (pos.y - cellY) * deltaY;
        } else { // SOUTH
            stepY = 1;
            sideDistY = (cellY + 1 - pos.y) * deltaY;
        }

        bool hit = false;
        int side = 0;
        while (!hit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaX;
                cellX += stepX;
                side = 0;
            } else {
                sideDistY += deltaY;
                cellY += stepY;
                side = 1;
            }

            if (mMap.get(cellX, cellY) == '1') {
                hit = true;
            }
        }

        float perpWallDist;
        if (!side) {
            perpWallDist = (sideDistX - deltaX);
        } else {
            perpWallDist = (sideDistY - deltaY);
        }

        int wallHeight = static_cast<int>(Config::windowSize.y / perpWallDist);
        int drawStart = std::max(0, -wallHeight / 2 + static_cast<int>(Config::windowSize.y) / 2);
        int drawEnd = std::min(static_cast<int>(Config::windowSize.y) - 1,
                               wallHeight / 2 + static_cast<int>(Config::windowSize.y) / 2);

        DrawCircle(cellX * mMap.getCellWidth(), cellY * mMap.getCellHeight(), 5, RED);
        DrawLine(x, drawStart, x, drawEnd, BLUE);
    }
}
