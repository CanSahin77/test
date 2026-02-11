#pragma once
#include <SFML/Graphics.hpp>

class Obstacle{
private:
    sf::RectangleShape obstacle;
public:
    Obstacle(sf::Vector2f position);
    void update(float delta, float speed);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};
