//
// Created by jgravier on 23/01/2023.
//

#include "Game.h"
#include "Config.h"
#include <raylib.h>
#include <iostream>
#include <cmath>

void Game::start() {
    std::cout << "Starting new game!" << std::endl;

    mPlayer.setPosition({
                                .x = mMap.getSpawnPoint().x * mMap.getCellWidth(),
                                .y = mMap.getSpawnPoint().y * mMap.getCellHeight()
                        });

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
    mPlayer.update();
}

void Game::render() {
    float halfFOV = Config::fieldOfView / 2;
    Vector2 dir = mPlayer.getDirection();
    Vector2 playerPos = mPlayer.getPosition();
    Vector2 pos = {
            playerPos.x / mMap.getCellWidth(),
            playerPos.y / mMap.getCellHeight()
    };

    for (int x = 0; x < static_cast<int>(Config::windowSize.x); x++) {
        float camX = 2.0f * static_cast<float>(x) / Config::windowSize.x - 1;
        Vector2 rayDir = {
                .x = dir.x - dir.y * camX,
                .y = dir.y + dir.x * camX
        };

        int cellX = static_cast<int>(pos.x);
        int cellY = static_cast<int>(pos.y);

        float deltaX = std::abs(1 / rayDir.x);
        float deltaY = std::abs(1 / rayDir.y);

        float sideDistX;
        float sideDistY;

        int stepX;
        int stepY;
        if (rayDir.x < 0) { // WEST
            stepX = -1;
            sideDistX = (pos.x - cellX) * deltaX;
        } else { // EAST
            stepX = 1;
            sideDistX = (cellX + 1 - pos.x) * deltaX;
        }

        if (rayDir.y < 0) { // NORTH
            stepY = -1;
            sideDistY = (pos.y - cellY) * deltaY;
        } else { // SOUTH
            stepY = 1;
            sideDistY = (cellY + 1 - pos.y) * deltaY;
        }

        bool hit = false;
        int side = 0;
        while (!hit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaX;
                cellX += stepX;
                side = 0;
            } else {
                sideDistY += deltaY;
                cellY += stepY;
                side = 1;
            }

            if (mMap.get(cellX, cellY) == '1') {
                hit = true;
            }
        }

        DrawCircle(cellX * mMap.getCellWidth(), cellY * mMap.getCellHeight(), 5, RED);

        float perpWallDist;
        if (!side) {
            perpWallDist = (sideDistX - deltaX);
        } else {
            perpWallDist = (sideDistY - deltaY);
        }

        int wallHeight = static_cast<int>(Config::windowSize.y / perpWallDist);
        int drawStart = std::max(0, -wallHeight / 2 + static_cast<int>(Config::windowSize.y) / 2);
        int drawEnd = std::min(static_cast<int>(Config::windowSize.y) - 1,
                               wallHeight / 2 + static_cast<int>(Config::windowSize.y) / 2);

        DrawLine(x, drawStart, x, drawEnd, BLUE);
    }

    mMap.render();
    mPlayer.render();
}
