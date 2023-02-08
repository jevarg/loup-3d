//
// Created by Jean on 1/27/2023.
//

#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include "Raycaster.h"
#include "Config.h"

enum HitSide {
    X = 0,
    Y
};

Raycaster::Raycaster(const Map &map, const Player &player, const Minimap &minimap) :
        mMap(map), mPlayer(player),
        mMinimap(minimap),
        mFloorTex(LoadTexture("assets/floor.png")),
        mFloorImg(LoadImage("assets/floor.png")) {}

void Raycaster::render(const Texture2D &wallTex) const {
    mRenderFloor();
    mRenderWalls(wallTex); // TODO: Return wall hit points?
}

void Raycaster::mRenderFloor() const {
    const Vector3 &playerPos = mPlayer.getPosition();
    const Vector2 &playerDir = mPlayer.getDirection();
    const Vector2 &leftRayDir = {
            playerDir.x + playerDir.y,
            playerDir.y - playerDir.x
    };

    const Vector2 &rightRayDir = {
            playerDir.x - playerDir.y,
            playerDir.y + playerDir.x
    };

    for (int y = static_cast<int>(Config::windowSize.y / 2) + 1; y < static_cast<int>(Config::windowSize.y); y++) {
        int pixelDist = y - static_cast<int>(Config::windowSize.y / 2);
        float rowDist = playerPos.z / pixelDist;

        const Vector2 &floorStep = {
                rowDist * (rightRayDir.x - leftRayDir.x) / Config::windowSize.x,
                rowDist * (rightRayDir.y - leftRayDir.y) / Config::windowSize.x,
        };

        Vector2 floorPoint = {
                playerPos.x + rowDist * leftRayDir.x,
                playerPos.y + rowDist * leftRayDir.y,
        };

        for (int x = 0; x < static_cast<int>(Config::windowSize.x); ++x) {
            int cellX = static_cast<int>(floorPoint.x);
            int cellY = static_cast<int>(floorPoint.y);

            floorPoint.x += floorStep.x;
            floorPoint.y += floorStep.y;

            int tx = mFloorTex.width * (floorPoint.x - cellX);
            int ty = mFloorTex.height * (floorPoint.y - cellY);
            const Rectangle &src = {
                    static_cast<float>(tx),
                    static_cast<float>(ty),
                    1,
                    1
            };

            const Rectangle &dest = {
                    static_cast<float>(x),
                    static_cast<float>(y),
                    1,
                    1
            };

            int offset = (((ty * mFloorImg.width) + tx) * 4) % (mFloorImg.width * mFloorImg.height);
            Color *pixel = reinterpret_cast<Color *>(static_cast<uint8_t *>(mFloorImg.data) + offset);
            DrawPixel(x, y, *pixel);
        }
    }
}

void Raycaster::mRenderWalls(const Texture2D &wallTex) const {
    const Vector2 &playerDir = mPlayer.getDirection();
    const Vector3 &playerPos = mPlayer.getPosition();
    std::vector<HitPoint> hitPoints;

    for (int x = 0; x < static_cast<int>(Config::windowSize.x); x++) {
        float camX = 2.0f * static_cast<float>(x) / Config::windowSize.x - 1;
        Vector2 rayDir = {
                .x = playerDir.x - playerDir.y * camX,
                .y = playerDir.y + playerDir.x * camX
        };

        uint8_t cellX = static_cast<uint8_t>(playerPos.x);
        uint8_t cellY = static_cast<uint8_t>(playerPos.y);

        float deltaX = std::abs(1 / rayDir.x);
        float deltaY = std::abs(1 / rayDir.y);

        float sideDistX;
        float sideDistY;

        int stepX;
        int stepY;
        if (rayDir.x < 0) { // WEST
            stepX = -1;
            sideDistX = (playerPos.x - cellX) * deltaX;
        } else { // EAST
            stepX = 1;
            sideDistX = (cellX + 1 - playerPos.x) * deltaX;
        }

        if (rayDir.y < 0) { // NORTH
            stepY = -1;
            sideDistY = (playerPos.y - cellY) * deltaY;
        } else { // SOUTH
            stepY = 1;
            sideDistY = (cellY + 1 - playerPos.y) * deltaY;
        }

        bool didHit = false;
        HitSide hitSide;
        while (!didHit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaX;
                cellX += stepX;
                hitSide = HitSide::X;
            } else {
                sideDistY += deltaY;
                cellY += stepY;
                hitSide = HitSide::Y;
            }

            if (mMap.get(cellX, cellY) == EntityType::Wall) {
                didHit = true;
            }
        }

        float perpendicularDist;
        if (hitSide == HitSide::X) {
            perpendicularDist = (sideDistX - deltaX);
        } else {
            perpendicularDist = (sideDistY - deltaY);
        }

        Vector2 hitPoint = {playerPos.x + perpendicularDist * rayDir.x,
                            playerPos.y + perpendicularDist * rayDir.y};

        hitPoints.push_back(HitPoint{hitPoint, perpendicularDist});

        float texX;
        if (hitSide == HitSide::X) {
            texX = (hitPoint.y - std::floor(hitPoint.y)) * wallTex.width;
        } else {
            texX = (hitPoint.x - std::floor(hitPoint.x)) * wallTex.width;
        }

        if (hitSide == HitSide::X && rayDir.x > 0) {
            texX = wallTex.width - texX - 1;
        }
        if (hitSide == HitSide::Y && rayDir.y < 0) {
            texX = wallTex.width - texX - 1;
        }

        int wallHeight = static_cast<int>(Config::windowSize.y / perpendicularDist);
        int drawStart = -wallHeight / 2 + static_cast<int>(Config::windowSize.y) / 2;
        int drawEnd = wallHeight / 2 + static_cast<int>(Config::windowSize.y) / 2;

        Rectangle rectSrc = {static_cast<float>(texX), 0, 1.0, static_cast<float>(wallTex.height)};
        Rectangle rectDst = {static_cast<float>(x), static_cast<float>(drawStart), 1,
                             static_cast<float>(drawEnd - drawStart)};


        uint8_t colorModifier = 255;
        if (Config::distantShadows && perpendicularDist > 1.0f) {
            colorModifier = std::max(static_cast<uint8_t>(colorModifier / perpendicularDist), Config::maxShadow);
        }

        Color tint = {colorModifier, colorModifier, colorModifier, 255};

        if (hitSide == HitSide::Y) {
            tint = {150, 150, 150, 255};
        }

        DrawTexturePro(wallTex, rectSrc, rectDst, {0, 0}, 0, tint);

//        if (drawEnd < Config::windowSize.y) {
//            DrawLine(x, drawEnd, x, Config::windowSize.y, GREEN);
//        }
//
//        if (drawStart > 0) {
//            DrawLine(x, 0, x, drawStart, BLUE);
//        }
    }
    mMinimap.drawPlayerFOV(hitPoints);
}
