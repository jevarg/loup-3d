//
// Created by jgravier on 23/01/2023.
//

#include "Game.h"
#include "Config.h"
#include <raylib.h>
#include <iostream>
#include <cmath>
#include <cassert>

void Game::start() {
    std::cout << "Starting new game!" << std::endl;
    auto blockWidth = Config::windowSize.x / m_map.getWidth();
    auto blockHeight = Config::windowSize.y / m_map.getHeight();

    m_player.setPosition({
        .x = m_map.getSpawnPoint().x * blockWidth,
        .y = m_map.getSpawnPoint().y * blockHeight
    });

    loop();
}

void Game::loop() {
    while (!m_window.shouldClose()) {
        PollInputEvents();
        update();

        ClearBackground(BLACK);
        BeginDrawing();
        render();
        EndDrawing();
    }
}

void Game::update() {
    m_player.update();
}

void Game::render() {
    DrawFPS(10, 10);

    float halfFOV = Config::fieldOfView / 2;
    Vector2 dir = m_player.getDirection();
    Vector2 playerPos = m_player.getPosition();

    int numberOfRays = Config::windowSize.x;
    float k = Config::fieldOfView / static_cast<float>(numberOfRays);

    for (int i = 0; i < numberOfRays; ++i) {
    float angle = (-halfFOV + (static_cast<float>(i) * k)) * DEG2RAD;
        Vector2 rayDir = {
                .x = dir.x * std::cos(angle) - dir.y * std::sin(angle),
                .y = dir.x * std::sin(angle) + dir.y * std::cos(angle)
        };

        // Drawing rays
        DrawLineV(playerPos,
                  {playerPos.x + rayDir.x * 100, playerPos.y + rayDir.y * 100},
                  GREEN);
    }

    m_map.render();
    m_player.render();
}
