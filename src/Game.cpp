//
// Created by jgravier on 23/01/2023.
//

#include "Game.h"
#include "Config.h"
#include <raylib.h>
#include <iostream>

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

    m_map.render();
    m_player.render();
}
