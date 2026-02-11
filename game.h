#pragma once
#include <SFML/Graphics.hpp>
#include "gamestate.h"
#include "menu.h"
#include "player.h"
#include "obstacles.h"
#include <vector>
class Game{
    private:
        sf::RenderWindow window;
        GameState state;
        Menu menu;
        Player player;
        void proccesEvent();
        void update();
        void render();
        std::vector<Obstacle> obstacles;
        sf::Clock clock;
        float delta;
        float obstacleSpeed = 400.f;
        sf::Clock spawnClock;
        void spawnObstacle();
    public:
        Game();
        void run();
};