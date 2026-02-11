#pragma once
#include <SFML/Graphics.hpp>
class Player{
    private:
        float gravity = 980.0f;
        float jumpspeed = -500.0f; 
        float velocity = 0.0f;
        sf::CircleShape sekil;
    public:
        sf::FloatRect getBounds() const;
        Player(sf::RenderWindow& window);
        void jump();
        void update(float a);
        void draw(sf::RenderWindow& window);
};