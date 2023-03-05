//
// Created by Jean on 1/29/2023.
//

#include "Minimap.h"
#include "Config.h"
#include "Raycaster.h"
#include <cmath>

Minimap::Minimap(const Player &player, const Map &map) : mPlayer(player), mMap(map),
                                                         mCellSize(map.getSize() * Config::mapScale) {}

void Minimap::render(FrameBuffer &frameBuffer) const {
    const std::vector<EntityType> mapData = mMap.getData();
    const jevarg::size<std::uint8_t> &mapSize = mMap.getSize();

    for (int i = 0; i < mapData.size(); i++) {
        jevarg::color color{};
        switch (mapData[i]) {
            case EntityType::Wall:
                color = jevarg::color::blue();
                break;
            default:
                continue;
        }

        int x = (i % mapSize.width) * mCellSize.width;
        int y = (i / mapSize.width) * mCellSize.height;

        frameBuffer.drawRectangle({x, y}, mCellSize, color);
    }

    const jevarg::vec3<float> &playerPos = mPlayer.getPosition();
    const jevarg::vec2<float> &playerDir = mPlayer.getDirection();
    float angle = std::atan2(playerDir.y, playerDir.x);

    frameBuffer.drawRectangle(
            {static_cast<int>(playerPos.x * mCellSize.width), static_cast<int>(playerPos.y * mCellSize.height)},
            {10, 10},
            angle,
            jevarg::color::red());

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
}

const jevarg::size<int> &Minimap::getCellSize() const {
    return mCellSize;
}
