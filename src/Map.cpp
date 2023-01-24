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
        return;
    }

    std::string line;
    uint8_t y = 0;
    bool spawnPointFound = false;

    while(std::getline(file, line)) {
        m_height++;
        if (!m_width) {
            m_width = line.length();
        }

        if (m_width != line.length()) {
            std::cerr << "Invalid map!" << std::endl;
            return;
        }

        uint8_t x = 0;
        for (char c : line) {
            m_data.push_back(c);
            if (c == '2' && !spawnPointFound) {
                m_spawnPoint.x = x;
                m_spawnPoint.y = y;
                spawnPointFound = true;
            }

            x++;
        }

        y++;
    }

    printf("Dimensions: %dx%d\n", m_width, m_height);
    printf("Spawn point: (%f, %f)\n", m_spawnPoint.x, m_spawnPoint.y);
    m_valid = true;

    file.close();
}

bool Map::isValid() const {
    return m_valid;
}

char Map::get(uint8_t x, uint8_t y) const {
    int pos = (y * m_width) + x;
    if (pos > m_data.size()) {
        printf("Invalid position: (%d, %d)\n", x, y);
        return 0;
    }

    return m_data[pos];
}

Vector2 Map::getSpawnPoint() const {
    return m_spawnPoint;
}

uint8_t Map::getWidth() const {
    return m_width;
}

uint8_t Map::getHeight() const {
    return m_height;
}

void Map::render() const {
    auto blockWidth = Config::windowSize.x / m_width;
    auto blockHeight = Config::windowSize.y / m_height;

    for (int i = 0; i < m_data.size(); i++) {
        Color color;
        switch (m_data[i]) {
            case '1':
                color = BLUE;
                break;
            default:
                continue;
        }

        int x = (i % m_width) * blockWidth;
        int y = (i / m_width) * blockHeight;

        DrawRectangle(x, y,blockWidth, blockHeight, color);
    }

    for (uint8_t i = 0; i < m_width; ++i) {
        DrawLine(i * blockWidth, 0, i * blockWidth, Config::windowSize.y, WHITE);
    }

    for (uint8_t i = 0; i < m_height; ++i) {
        DrawLine(0, i * blockHeight, Config::windowSize.x, i * blockHeight, WHITE);
    }
}
