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
//    FrameBuffer &frameBuffer = mWindow.getFrameBuffer();
//    for (int i = 0; i < 256; ++i) {
//        jevarg::color c{
//                static_cast<uint8_t>((colorPalette[i] & 0xff0000) >> 16),
//                static_cast<uint8_t>((colorPalette[i] & 0x00ff00) >> 8),
//                static_cast<uint8_t>(colorPalette[i] & 0x0000ff),
//                0xff
//        };
//
//        int size = 10;
//        jevarg::vec2<int> pos{(i * size) % (Config::rendererSize.width - size),
//                              ((i * size) / (Config::rendererSize.width - size)) * size};
//
//        frameBuffer.drawRectangle(pos, {size, size}, c);
//    }
//    return;
    mRaycaster.render(mWindow.getFrameBuffer(), mResourceMgr);
    mMinimap.render(mWindow.getFrameBuffer());

    FrameBuffer &fb = mWindow.getFrameBuffer();
    fb.filter();
    // fb
}
