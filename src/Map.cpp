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
        mSize.height++;
        if (!mSize.width) {
            mSize.width = static_cast<uint8_t>(line.length());
        }

        if (mSize.width != line.length()) {
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
                mSpawnPoint.z = static_cast<int>(Config::windowSize.height * 0.5f);
                spawnPointFound = true;
            }

            x++;
        }

        y++;
    }

    printf("Dimensions: %dx%d\n", mSize.width, mSize.height);
    printf("Spawn point: (%d, %d)\n", mSpawnPoint.x, mSpawnPoint.y);
    mValid = true;

    file.close();
}

bool Map::isValid() const {
    return mValid;
}

EntityType Map::get(uint8_t x, uint8_t y) const {
    int pos = (y * mSize.width) + x;
    if (pos > mData.size()) {
        printf("Invalid position: (%d, %d)\n", x, y);
        return EntityType::Invalid;
    }

    return mData[pos];
}

const jevarg::vec3<int> &Map::getSpawnPoint() const {
    return mSpawnPoint;
}

const jevarg::size<uint8_t> &Map::getSize() const {
    return mSize;
}

void Map::render() const {}

const std::vector<EntityType> &Map::getData() const {
    return mData;
}
