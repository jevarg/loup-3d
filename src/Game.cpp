//
// Created by jgravier on 23/01/2023.
//

#include "Game.h"
#include "Config.h"
#include <iostream>
#include <cmath>

Game::Game() : mMap("first.map"),
               mMinimap(mPlayer, mMap),
               mRaycaster(mMap,
                          mPlayer,
                          mMinimap) {
    mResourceMgr.loadResources();
}

void Game::start() {
    if (!mMap.isValid()) {
        std::cerr << "Could not start game! Map is not valid" << std::endl;
        return;
    }

    std::cout << "Starting new game!" << std::endl;
    mPlayer.setPosition(static_cast<jevarg::vec3<float>>(mMap.getSpawnPoint()));
    loop();
}

void Game::loop() {
    while (!mWindow.shouldClose()) {
        mWindow.clear();
        update();
        render();
        mWindow.swapBuffers();
        mWindow.present();

        SDL_Delay(1000 / Config::maxFPS); // TODO: FPS counter
    }
}

void Game::update() {
    mWindow.update();

    jevarg::vec3 prevPos = mPlayer.getPosition();
    mPlayer.update(mWindow.getInputManager());

    jevarg::vec3 pos = mPlayer.getPosition();
    jevarg::vec2 playerCellPos = {std::floor(pos.x), std::floor(pos.y)};

    if (mMap.get(static_cast<uint8_t>(playerCellPos.x), static_cast<uint8_t>(playerCellPos.y)) == EntityType::Wall) {
        mPlayer.setPosition(prevPos);
    }
}

void Game::render() {
    mRaycaster.render(mWindow.getFrameBuffer(), mResourceMgr);
    mMinimap.render(mWindow.getFrameBuffer());
}
