//
// Created by jgravier on 23/01/2023.
//

#include <fstream>
#include <iostream>
#include "Map.h"
#include "Config.h"

Map::Map(const std::string &filePath) {
    printf("Loading map: %s\n", filePath.c_str());

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Could not open map: " << filePath << std::endl;
        return;
    }

    std::string line;
    uint8_t y = 0;
    bool spawnPointFound = false;

    while(std::getline(file, line)) {
        mHeight++;
        if (!mWidth) {
            mWidth = line.length();
        }

        if (mWidth != line.length()) {
            std::cerr << "Invalid map!" << std::endl;
            return;
        }

        uint8_t x = 0;
        for (char c : line) {
            if (c < '0' || c > '9') {
                mValid = false;
                file.close();
                std::cerr << "Invalid map: invalid char '" << c << "' at (" << +x << "," << +y << ")" << std::endl;
                return;
            }

            mData.push_back(static_cast<EntityType>(c - '0'));
            if (c == '2' && !spawnPointFound) {
                mSpawnPoint.x = x;
                mSpawnPoint.y = y;
                mSpawnPoint.z = Config::windowSize.y * 0.5;
                spawnPointFound = true;
            }

            x++;
        }

        y++;
    }

    printf("Dimensions: %dx%d\n", mWidth, mHeight);
    printf("Spawn point: (%f, %f)\n", mSpawnPoint.x, mSpawnPoint.y);
    mValid = true;

    file.close();
}

bool Map::isValid() const {
    return mValid;
}

EntityType Map::get(uint8_t x, uint8_t y) const {
    int pos = (y * mWidth) + x;
    if (pos > mData.size()) {
        printf("Invalid position: (%d, %d)\n", x, y);
        return EntityType::Invalid;
    }

    return mData[pos];
}

const Vector3 &Map::getSpawnPoint() const {
    return mSpawnPoint;
}

uint8_t Map::getWidth() const {
    return mWidth;
}

uint8_t Map::getHeight() const {
    return mHeight;
}

void Map::render() const {}

const std::vector<EntityType> &Map::getData() const {
    return mData;
}
