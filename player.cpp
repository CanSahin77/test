#include "player.h"
Player::Player(sf::RenderWindow& window):
    sekil(50.0f)
{
    sekil.setFillColor(sf::Color::Red);
    float x = (window.getSize().x / 2.0f) - sekil.getRadius();
    float y = (window.getSize().y / 2.0f) - sekil.getRadius();
    sf::Vector2f position = sf::Vector2f(x,y);
    sekil.setPosition(position);

}
sf::FloatRect Player::getBounds() const{
    return sekil.getGlobalBounds();
}

void Player::update(float delta){
    velocity += gravity * delta;
    sekil.move(sf::Vector2f(0.0f, velocity * delta));
}
void Player::jump(){
    velocity = jumpspeed;
}
void Player::draw(sf::RenderWindow& window){
    window.draw(sekil);

}