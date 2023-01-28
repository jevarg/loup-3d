//
// Created by jgravier on 23/01/2023.
//

#pragma once

#include <string>
#include <vector>
#include <raylib.h>

class Map {
public:
    explicit Map(const std::string &filePath);

    bool isValid() const;
    Vector2 getSpawnPoint() const;

    uint8_t getWidth() const;
    uint8_t getHeight() const;

    int getCellWidth() const;
    int getCellHeight() const;

    char get(uint8_t x, uint8_t y) const;
    void render() const;

private:
    std::vector<char> mData;
    bool mValid = false;

    uint8_t mWidth = 0;
    uint8_t mHeight = 0;

    Vector2 mSpawnPoint = { };

    int mCellWidth = 0;
    int mCellHeight = 0;
};
