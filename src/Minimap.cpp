//
// Created by Jean on 1/29/2023.
//

#include "Minimap.h"
#include "Config.h"
#include "Raycaster.h"
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846f
#endif
#ifndef DEG2RAD
#define DEG2RAD (PI/180.0f)
#endif
#ifndef RAD2DEG
#define RAD2DEG (180.0f/PI)
#endif

Minimap::Minimap(const Player &player, const Map &map) : mPlayer(player), mMap(map),
                                                         mCellSize(map.getSize() * Config::mapScale) {}

void Minimap::render(FrameBuffer &frameBuffer) const {
    const std::vector<EntityType> mapData = mMap.getData();
    const jevarg::size<std::uint8_t> &mapSize = mMap.getSize();

    for (int i = 0; i < mapData.size(); i++) {
        jevarg::color color;
        switch (mapData[i]) {
            case EntityType::Wall:
                color = jevarg::color::blue();
                break;
//            default:
//                continue;
//                color = GRAY;
//                break;
        }

        int x = (i % mapSize.width) * mCellSize.width;
        int y = (i / mapSize.width) * mCellSize.height;

//        DrawRectangle(x, y, mCellSize.width, mCellSize.height, color);
    }

    const jevarg::vec3<float> &playerPos = mPlayer.getPosition();
    const jevarg::vec2<float> &playerDir = mPlayer.getDirection();
    float angle = std::atan2(playerDir.y, playerDir.x) * RAD2DEG;
    SDL_Rect r = {static_cast<int>(playerPos.x * mCellSize.width), static_cast<int>(playerPos.y * mCellSize.height), 10,
                  10};

//    DrawRectanglePro(r, {r.width / 2, r.height / 2}, angle, RED);
    frameBuffer.drawLine(
            {static_cast<int>(playerPos.x * mCellSize.width), static_cast<int>(playerPos.y * mCellSize.height)},
            {static_cast<int>(playerPos.x * mCellSize.width + playerDir.x * 100),
             static_cast<int>(playerPos.y * mCellSize.height + playerDir.y * 100)},
            jevarg::color::green());
}

void Minimap::drawPlayerFOV(FrameBuffer &frameBuffer, const std::vector<HitPoint> &hitPoints) const {
    const jevarg::vec3<float> &playerPos = mPlayer.getPosition();

    for (const auto &hitPoint: hitPoints) {
        frameBuffer.drawLine(
                {static_cast<int>(playerPos.x * mCellSize.width),
                 static_cast<int>(playerPos.y * mCellSize.height)},
                {static_cast<int>(hitPoint.point.x * mCellSize.width),
                 static_cast<int>(hitPoint.point.y * mCellSize.height)}, jevarg::color::yellow());
    }
//    int prev = 0;
//    for (int i = 0; i < hitPoints.size(); ++i) {
//        if (i == 0) {
//            DrawLine(playerPos.x * mCellSize.width, playerPos.y * mCellSize.height,
//                     hitPoints[i].point.x * mCellSize.width, hitPoints[i].point.y * mCellSize.height, YELLOW);
//        } else if (i == hitPoints.size() - 1) {
//            DrawLine(hitPoints[i].point.x * mCellSize.width, hitPoints[i].point.y * mCellSize.height,
//                     playerPos.x * mCellSize.width, playerPos.y * mCellSize.height, YELLOW);
//        } else if (hitPoints[prev].dist != hitPoints[i].dist) {
//            DrawLine(hitPoints[prev].point.x * mCellSize.width, hitPoints[prev].point.y * mCellSize.height,
//                     hitPoints[i].point.x * mCellSize.width, hitPoints[i].point.y * mCellSize.height, YELLOW);
//        }
//
//        prev = i;
//    }
}

const jevarg::size<int> &Minimap::getCellSize() const {
    return mCellSize;
}
