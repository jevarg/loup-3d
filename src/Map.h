//
// Created by jgravier on 23/01/2023.
//

#pragma once

#include <string>
#include <vector>
#include <raylib.h>
#include "EntityType.h"

class Map {
public:
    explicit Map(const std::string &filePath);

    bool isValid() const;
    const Vector3 &getSpawnPoint() const;

    uint8_t getWidth() const;
    uint8_t getHeight() const;

    EntityType get(uint8_t x, uint8_t y) const;
    const std::vector<EntityType> &getData() const;
    void render() const;

private:
    std::vector<EntityType> mData;
    bool mValid = false;

    uint8_t mWidth = 0;
    uint8_t mHeight = 0;

    Vector3 mSpawnPoint = { };
};
