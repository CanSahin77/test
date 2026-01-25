#pragma once
#include <SFML/Graphics.hpp>
enum class GameState;
class Menu{
    private:
        sf::RectangleShape ikinciKatman;
        sf::RectangleShape kutu;
        sf::RectangleShape devamButon;
        sf::RectangleShape cikButon;
    public:
        Menu(sf::Vector2f windowsize);
        void toggle(GameState& state);
        bool dvbutontiklama(sf::Vector2f mousepos);
        bool cikbutontiklama(sf::Vector2f mousepos);
        void draw(sf::RenderWindow& window);
};