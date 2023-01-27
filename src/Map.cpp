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
            mData.push_back(c);
            if (c == '2' && !spawnPointFound) {
                mSpawnPoint.x = x;
                mSpawnPoint.y = y;
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

    mCellWidth = mWidth * Config::mapScale;
    mCellHeight = mHeight * Config::mapScale;
}

bool Map::isValid() const {
    return mValid;
}

char Map::get(uint8_t x, uint8_t y) const {
    int pos = (y * mWidth) + x;
    if (pos > mData.size()) {
        printf("Invalid position: (%d, %d)\n", x, y);
        return 0;
    }

    return mData[pos];
}

Vector2 Map::getSpawnPoint() const {
    return mSpawnPoint;
}

uint8_t Map::getWidth() const {
    return mWidth;
}

uint8_t Map::getHeight() const {
    return mHeight;
}

void Map::render() const {
    for (int i = 0; i < mData.size(); i++) {
        Color color;
        switch (mData[i]) {
            case '1':
                color = BLUE;
                break;
            default:
                continue;
        }

        int x = (i % mWidth) * mCellWidth;
        int y = (i / mWidth) * mCellHeight;

        DrawRectangle(x, y,mCellWidth, mCellHeight, color);
    }

    for (uint8_t i = 0; i < mWidth; ++i) {
        DrawLine(i * mCellWidth, 0, i * mCellWidth, mHeight * mCellHeight, WHITE);
    }

    for (uint8_t i = 0; i < mHeight; ++i) {
        DrawLine(0, i * mCellHeight, mWidth * mCellWidth, i * mCellHeight, WHITE);
    }
}

int Map::getCellWidth() const {
    return mCellWidth;
}

int Map::getCellHeight() const {
    return mCellHeight;
}
