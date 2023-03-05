//
// Created by Jean on 1/27/2023.
//

#include <cmath>
#include "Raycaster.h"
#include "Config.h"
#include "ResourceManager.h"
#include "Texture.h"

enum HitSide {
    X = 0,
    Y
};

Raycaster::Raycaster(const Map &map, const Player &player, const Minimap &minimap) :
        mMap(map),
        mPlayer(player),
        mMinimap(minimap) {}

void Raycaster::render(FrameBuffer &frameBuffer, const ResourceManager &resourceMgr) {
    mRenderFloor(frameBuffer, resourceMgr);
    mRenderWalls(frameBuffer, resourceMgr); // TODO: Return wall hit points?
}

void Raycaster::mRenderFloor(FrameBuffer &frameBuffer, const ResourceManager &resourceMgr) {
    SDL_Surface *tex = resourceMgr.getTexture(ResourceID::TEX_FLOOR_1);
    const jevarg::vec3<float> &playerPos = mPlayer.getPosition();
    const jevarg::vec2<float> &playerDir = mPlayer.getDirection();
    const jevarg::vec2<float> &leftRayDir = {
            playerDir.x + playerDir.y,
            playerDir.y - playerDir.x
    };

    const jevarg::vec2<float> &rightRayDir = {
            playerDir.x - playerDir.y,
            playerDir.y + playerDir.x
    };

    for (int y = Config::windowSize.height / 2 + 1; y < Config::windowSize.height; y++) {
        int pixelDist = y - Config::windowSize.height / 2;
        float rowDist = playerPos.z / pixelDist;

        const jevarg::vec2<float> &floorStep = {
                rowDist * (rightRayDir.x - leftRayDir.x) / Config::windowSize.width,
                rowDist * (rightRayDir.y - leftRayDir.y) / Config::windowSize.width,
        };

        jevarg::vec2<float> floorPoint = {
                playerPos.x + rowDist * leftRayDir.x,
                playerPos.y + rowDist * leftRayDir.y,
        };

        for (int x = 0; x < Config::windowSize.width; ++x) {
            int cellX = static_cast<int>(floorPoint.x);
            int cellY = static_cast<int>(floorPoint.y);

            int tx = static_cast<int>(tex->w * (floorPoint.x - cellX)) & (tex->w - 1);
            int ty = static_cast<int>(tex->h * (floorPoint.y - cellY)) & (tex->h - 1);

            floorPoint.x += floorStep.x;
            floorPoint.y += floorStep.y;

            int texOffset = (ty * tex->w + tx) * tex->format->BytesPerPixel;
            jevarg::color *pixel = reinterpret_cast<jevarg::color *>(static_cast<uint8_t *>(tex->pixels) + texOffset);
            frameBuffer.drawPixel(x, y, *pixel);
        }
    }
}

void Raycaster::mRenderWalls(FrameBuffer &frameBuffer, const ResourceManager &resourceMgr) {
    const jevarg::vec2<float> &playerDir = mPlayer.getDirection();
    const jevarg::vec3<float> &playerPos = mPlayer.getPosition();
    SDL_Surface *tex = resourceMgr.getTexture(ResourceID::TEX_WALL_1);
    std::vector<HitPoint> hitPoints;

    for (int x = 0; x < static_cast<int>(Config::windowSize.width); x++) {
        float camX = 2.0f * static_cast<float>(x) / Config::windowSize.width - 1;
        jevarg::vec2<float> rayDir{
                playerDir.x - playerDir.y * camX,
                playerDir.y + playerDir.x * camX
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

        jevarg::vec2<float> hitPoint = {playerPos.x + perpendicularDist * rayDir.x,
                                        playerPos.y + perpendicularDist * rayDir.y};

        hitPoints.push_back(HitPoint{hitPoint, perpendicularDist});

        int texX;
        if (hitSide == HitSide::X) {
            texX = static_cast<int>((hitPoint.y - std::floor(hitPoint.y)) * tex->w);
        } else {
            texX = static_cast<int>((hitPoint.x - std::floor(hitPoint.x)) * tex->w);
        }

        if ((hitSide == HitSide::X && rayDir.x > 0) ||
            (hitSide == HitSide::Y && rayDir.y < 0)) {
            texX = tex->w - texX - 1;
        }

        int wallHeight = static_cast<int>(Config::windowSize.height / perpendicularDist);
        int drawStart = -wallHeight / 2 + static_cast<int>(Config::windowSize.height) / 2;
        int drawEnd = std::min(Config::windowSize.height,
                               wallHeight / 2 + static_cast<int>(Config::windowSize.height) / 2);

        float texStep = static_cast<float>(tex->h) / static_cast<float>(wallHeight);
        for (int y = drawStart; y < drawEnd; ++y) {
            if (y < 0) {
                continue;
            }

            int texY = static_cast<int>(texStep * (y - drawStart)) % tex->h;
            int texOffset = (texY * tex->w + texX) * tex->format->BytesPerPixel;

            jevarg::color *pixel = reinterpret_cast<jevarg::color *>(static_cast<uint8_t *>(tex->pixels) + texOffset);
            frameBuffer.drawPixel(x, y, *pixel);
        }
    }

    mMinimap.drawPlayerFOV(frameBuffer, hitPoints);
}
