//
// Created by jgravier on 23/01/2023.
//

#include "Game.h"
#include <raylib.h>
#include <iostream>

Game::Game() : mMap("../first.map"), mRaycaster(mMap, mPlayer) {}

void Game::start() {
    std::cout << "Starting new game!" << std::endl;

    mPlayer.setPosition({mMap.getSpawnPoint().x * mMap.getCellWidth(),
                         mMap.getSpawnPoint().y * mMap.getCellHeight()});

    loop();
}

void Game::loop() {
    while (!mWindow.shouldClose()) {
        PollInputEvents();
        update();

        ClearBackground(BLACK);
        BeginDrawing();
        render();
        DrawFPS(10, 10); // DEBUG
        EndDrawing();
    }
}

void Game::update() {
    Vector2 prevPos = mPlayer.getPosition();
    mPlayer.update();

    Vector2 pos = mPlayer.getPosition();
    Vector2 playerCellPos = {pos.x / mMap.getCellWidth(), pos.y / mMap.getCellHeight()};

    if (mMap.get(static_cast<uint8_t>(playerCellPos.x), static_cast<uint8_t>(playerCellPos.y)) == '1') {
        mPlayer.setPosition(prevPos);
    }
}

void Game::render() {
    mRaycaster.render();
    mMap.render();
    mPlayer.render();
}
