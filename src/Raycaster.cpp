//
// Created by Jean on 1/27/2023.
//

#include <raylib.h>
#include <cmath>
#include "Raycaster.h"
#include "Config.h"

Raycaster::Raycaster(const Map &map, const Player &player) : mMap(map), mPlayer(player) {}

void Raycaster::render(const Texture2D &wallTex) const {
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
        float hitX, hitY;
//        float hitYOffset;
        if (side == 0) {
            perpWallDist = (sideDistX - deltaX);
            hitX = pos.y + perpWallDist * rayDir.y;
            hitY = pos.x + perpWallDist * rayDir.x;
        } else {
            perpWallDist = (sideDistY - deltaY);
            hitX = pos.x + perpWallDist * rayDir.x;
            hitY = pos.y + perpWallDist * rayDir.y;
        }

        hitX -= std::floor(hitX);
        hitY -= std::floor(hitY);

        float texX = hitX * wallTex.width;

        if (side == 0 && rayDir.x > 0) {
            texX = wallTex.width - texX - 1;
        }
        if (side == 1 && rayDir.y < 0) {
            texX = wallTex.width - texX - 1;
        }

        int wallHeight = static_cast<int>(Config::windowSize.y / perpWallDist);
        int drawStart = std::max(0, -wallHeight / 2 + static_cast<int>(Config::windowSize.y) / 2);
        int drawEnd = std::min(static_cast<int>(Config::windowSize.y) - 1,
                               wallHeight / 2 + static_cast<int>(Config::windowSize.y) / 2);

        Rectangle rectSrc = {static_cast<float>(texX), 0, 1.0, static_cast<float>(wallTex.height)};
        Rectangle rectDst = {static_cast<float>(x), static_cast<float>(drawStart), 1, static_cast<float>(drawEnd - drawStart)};

        uint8_t colorModifier = static_cast<int>(255 / perpWallDist);
        if (colorModifier < 100) colorModifier = 100;
        Color tint = {colorModifier, colorModifier, colorModifier, 255};

        DrawTexturePro(wallTex, rectSrc, rectDst, {0, 0}, 0, tint);
        DrawCircle(hitX * mMap.getCellWidth(), hitY * mMap.getCellHeight(), 2, RED);
        DrawLineV(playerPos, {hitX * mMap.getCellWidth(), hitY * mMap.getCellHeight()}, GREEN);
    }
}
