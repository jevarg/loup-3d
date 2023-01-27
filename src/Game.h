//
// Created by jgravier on 23/01/2023.
//

#pragma once

#include "Window.h"
#include "Map.h"
#include "Player.h"

class Game {
public:
    Game() = default;
    ~Game() = default;

    void start();

private:
    void loop();
    void update();
    void render();

    Window mWindow;
    Map mMap = Map("../first.map");
    Player mPlayer;
};
