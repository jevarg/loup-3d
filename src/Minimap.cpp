//
// Created by Jean on 1/29/2023.
//

#include "Minimap.h"
#include "Config.h"
#include "Raycaster.h"
#include <cmath>

Minimap::Minimap(const Player &player, const Map &map) : mPlayer(player), mMap(map),
                                                         mCellSize(map.getSize() * Config::mapScale) {}

void Minimap::render() const {
    const std::vector<EntityType> mapData = mMap.getData();

//    for (int i = 0; i < mapData.size(); i++) {
//        Color color;
//        switch (mapData[i]) {
//            case EntityType::Wall:
//                color = BLUE;
//                break;
//            default:
//                continue;
//                color = GRAY;
//                break;
//        }
//
//        int x = (i % mMap.getWidth()) * mCellSize.width;
//        int y = (i / mMap.getWidth()) * mCellSize.height;
//
//        DrawRectangle(x, y, mCellSize.width, mCellSize.height, color);
//    }
//
//    const Vector3 &playerPos = mPlayer.getPosition();
//    const Vector2 &playerDir = mPlayer.getDirection();
//    float angle = std::atan2(playerDir.y, playerDir.x) * RAD2DEG;
//    Rectangle r = {playerPos.x * mCellSize.width, playerPos.y * mCellSize.height, 10, 10};
//
//    DrawRectanglePro(r, {r.width / 2, r.height / 2}, angle, RED);
//    DrawLine(playerPos.x * mCellSize.width, playerPos.y * mCellSize.height, playerPos.x * mCellSize.width + playerDir.x * 100, playerPos.y * mCellSize.height + playerDir.y * 100, GREEN);
}

void Minimap::drawPlayerFOV(const std::vector<HitPoint> &hitPoints) const {
//    const Vector3 &playerPos = mPlayer.getPosition();
//
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
