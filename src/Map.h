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
    char get(uint8_t x, uint8_t y) const;

    void render() const;

private:
    std::vector<char> m_data;
    bool m_valid = false;
    uint8_t m_width = 0;
    uint8_t m_height = 0;
    Vector2 m_spawnPoint = { };
};
