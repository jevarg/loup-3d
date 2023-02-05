//
// Created by jgravier on 23/01/2023.
//

#include "Game.h"
#include "Config.h"
#include <raylib.h>
#include <iostream>
#include <cmath>

Game::Game() : mMap("first.map"),
               mMinimap(mPlayer, mMap),
               mRaycaster(mMap, mPlayer, mMinimap),
               mWallTex(LoadTexture("assets/wall.png")) {
}

void Game::start() {
    if (!mMap.isValid()) {
        std::cerr << "Could not start game! Map is not valid" << std::endl;
        return;
    }

    std::cout << "Starting new game!" << std::endl;
    mPlayer.setPosition(mMap.getSpawnPoint());
    loop();
}

void Game::loop() {
    while (!mWindow.shouldClose()) {
        PollInputEvents();
        update();

        ClearBackground(BLACK);
        BeginDrawing();
        render();
        DrawFPS(Config::windowSize.x - 90, 10); // DEBUG
        EndDrawing();
    }
}

void Game::update() {
    Vector3 prevPos = mPlayer.getPosition();
    mPlayer.update();

    Vector3 pos = mPlayer.getPosition();
    Vector2 playerCellPos = {std::floor(pos.x), std::floor(pos.y)};

    if (mMap.get(static_cast<uint8_t>(playerCellPos.x), static_cast<uint8_t>(playerCellPos.y)) == EntityType::Wall) {
        mPlayer.setPosition(prevPos);
    }
}

void Game::render() {
    mRaycaster.render(mWallTex);
    mMinimap.render();
}
