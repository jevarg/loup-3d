//
// Created by jgravier on 23/01/2023.
//

#pragma once

#include "Window.h"
#include "Map.h"
#include "Player.h"
#include "Raycaster.h"

class Game {
public:
    explicit Game();
    ~Game() = default;

    void start();

private:
    void loop();
    void update();
    void render();

    Window mWindow;
    Map mMap;
    Raycaster mRaycaster;
    Player mPlayer;
    Texture2D mWallTex;
};
