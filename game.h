#pragma once
#include <SFML/Graphics.hpp>
#include "gamestate.h"
#include "menu.h"

class Game{
    private:
        sf::RenderWindow window;
        GameState state;
        Menu menu;
        void proccesEvent();
        void update();
        void render();
    public:
        Game();
        void run();
};