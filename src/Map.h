//
// Created by jgravier on 23/01/2023.
//

#pragma once

#include <string>
#include <vector>
#include <jevarg.h>
#include "EntityType.h"

class Map {
public:
    explicit Map(const std::string &filePath);

    bool isValid() const;
    const jevarg::vec3<int> &getSpawnPoint() const;
    const jevarg::size<uint8_t> &getSize() const;

    EntityType get(uint8_t x, uint8_t y) const;
    const std::vector<EntityType> &getData() const;
    void render() const;

private:
    std::vector<EntityType> mData;
    bool mValid = false;

    jevarg::size<uint8_t> mSize{0};
    jevarg::vec3<int> mSpawnPoint{0};
};
