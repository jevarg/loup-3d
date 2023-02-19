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

Raycaster::Raycaster(const Map &map, const Player &player, const Minimap &minimap, Texture *renderTexture) :
        mMap(map), mPlayer(player), mMinimap(minimap), mRenderTexture(renderTexture) {}

void Raycaster::render(const Renderer &renderer, const ResourceManager &resourceMgr) const {
//    mRenderTexture->lock();
//    mRenderFloor(renderer, resourceMgr);
//    renderer.renderTexture(*mRenderTexture);
    mRenderWalls(renderer, resourceMgr); // TODO: Return wall hit points?
//    mRenderTexture->unlock();
}

void Raycaster::mRenderFloor(const Renderer &renderer, const ResourceManager &resourceMgr) const {
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

    SDL_Color pixel{0, 255, 0, 255};
    std::uint8_t *buffer = new std::uint8_t[Config::windowSize.width * Config::windowSize.height * 4];

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

            floorPoint.x += floorStep.x;
            floorPoint.y += floorStep.y;

            int tx = tex->w * (floorPoint.x - cellX);
            int ty = tex->h * (floorPoint.y - cellY);

            const SDL_Rect &src = {tx, ty, 1, 1};
            const SDL_Rect &dest = {x, y, 1, 1};

//            SDL_RenderCopy(renderer, tex->getNativeTexture(), &src, &dest);
//            SDL_renderCop
//            if (r) {
//                printf("error: %s\n", SDL_GetError());
//            }

//            int offset = (((ty * tex->w) + tx) * 3) % (tex->w * tex->h);
//            SDL_Color *pixel = reinterpret_cast<SDL_Color *>(static_cast<uint8_t *>(tex->pixels) + offset);
//            testSurface->pixels


            int sOffset = (((y * Config::windowSize.width) + x) * 4) %
                          (Config::windowSize.width * Config::windowSize.height * 4);
//            uint8_t *toFill = static_cast<uint8_t *>(testSurface->pixels) + sOffset;
            (buffer + sOffset)[0] = pixel.r;
            (buffer + sOffset)[1] = pixel.g;
            (buffer + sOffset)[2] = pixel.b;
            (buffer + sOffset)[3] = pixel.a;

//            SDL_RenderDrawPoint(renderer, x, y);

//             TODO: Too many fucking draw calls
//            DrawTextureRec(mFloorTex, src, {static_cast<float>(x), static_cast<float>(y)}, WHITE);
//            DrawPixel(x, y, *pixel);
        }
    }
    mRenderTexture->copyBuffer(buffer);
    delete[] buffer;
}

void Raycaster::mRenderWalls(const Renderer &renderer, const ResourceManager &resourceMgr) const {
    const jevarg::vec2<float> &playerDir = mPlayer.getDirection();
    const jevarg::vec3<float> &playerPos = mPlayer.getPosition();
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

//        float texX;
//        if (hitSide == HitSide::X) {
//            texX = (hitPoint.y - std::floor(hitPoint.y)) * wallTex.width;
//        } else {
//            texX = (hitPoint.x - std::floor(hitPoint.x)) * wallTex.width;
//        }
//
//        if (hitSide == HitSide::X && rayDir.x > 0) {
//            texX = wallTex.width - texX - 1;
//        }
//        if (hitSide == HitSide::Y && rayDir.y < 0) {
//            texX = wallTex.width - texX - 1;
//        }
//
        int wallHeight = static_cast<int>(Config::windowSize.height / perpendicularDist);
        int drawStart = -wallHeight / 2 + static_cast<int>(Config::windowSize.height) / 2;
        int drawEnd = wallHeight / 2 + static_cast<int>(Config::windowSize.height) / 2;

        SDL_SetRenderDrawColor(renderer.getMNativeRenderer(), 255, 0, 0, 255);
        SDL_RenderDrawLineF(renderer.getMNativeRenderer(), x, drawStart, x, drawEnd);
//
//        Rectangle rectSrc = {static_cast<float>(texX), 0, 1.0, static_cast<float>(wallTex.height)};
//        Rectangle rectDst = {static_cast<float>(x), static_cast<float>(drawStart), 1,
//                             static_cast<float>(drawEnd - drawStart)};
//
//
//        uint8_t colorModifier = 255;
//        if (Config::distantShadows && perpendicularDist > 1.0f) {
//            colorModifier = std::max(static_cast<uint8_t>(colorModifier / perpendicularDist), Config::maxShadow);
//        }
//
//        Color tint = {colorModifier, colorModifier, colorModifier, 255};
//
//        if (hitSide == HitSide::Y) {
//            tint = {150, 150, 150, 255};
//        }
//
//        DrawTexturePro(wallTex, rectSrc, rectDst, {0, 0}, 0, tint);

        // NOTE: Render based on wall hitpoint
//        if (drawEnd < Config::windowSize.height) {
//            DrawLine(x, drawEnd, x, Config::windowSize.height, GREEN);
//        }
//
//        if (drawStart > 0) {
//            DrawLine(x, 0, x, drawStart, BLUE);
//        }
    }
    mMinimap.drawPlayerFOV(hitPoints);
}
