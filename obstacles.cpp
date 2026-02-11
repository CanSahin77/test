#include "obstacles.h"

Obstacle::Obstacle(sf::Vector2f position){
    obstacle.setSize({100.f, 1080.f});
    obstacle.setPosition(position);
    obstacle.setFillColor(sf::Color::Green);
}

void Obstacle::update(float delta, float speed){
    obstacle.move(sf::Vector2f(-speed * delta, 0.f));
}


void Obstacle::draw(sf::RenderWindow& window){
    window.draw(obstacle);
}

sf::FloatRect Obstacle::getBounds() const{
    return obstacle.getGlobalBounds();
}
