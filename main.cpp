#include <SFML/Graphics.hpp>
enum class GameState{
    Pause,
    Play
};
class Menu{
    private:
        sf::RectangleShape ikinciKatman;
        sf::RectangleShape kutu;
        sf::RectangleShape devamButon;
        sf::RectangleShape cikButon;
    public:
        Menu(sf::Vector2f windowsize){
            windowsize.x;
            windowsize.y;
            sf::Vector2f btnsize(250.f,50.f);
            ikinciKatman.setSize(windowsize);
            ikinciKatman.setPosition({0.f,0.f});
            ikinciKatman.setFillColor(sf::Color(0,0,0,150));   
            kutu.setSize({500.f,250.f});
            kutu.setPosition(sf::Vector2f(windowsize.x / 2.f - 250.f , windowsize.y / 2.f - 125.f ));
            kutu.setFillColor(sf::Color(50,50,50));
            devamButon.setSize(btnsize);
            devamButon.setPosition({kutu.getPosition().x + 125 , kutu.getPosition().y + 50.f});
            devamButon.setFillColor(sf::Color(200,0,0));
            cikButon.setSize(btnsize);
            cikButon.setPosition({kutu.getPosition().x + 125 , kutu.getPosition().y + 110.f});
            cikButon.setFillColor(sf::Color(200,0,0));

        }
        void toggle(GameState& state){
            if(state == GameState::Play){
                state = GameState::Pause;
            }else{
                state = GameState::Play;
            }
        };
        void draw(sf::RenderWindow& window){
            window.draw(ikinciKatman);
            window.draw(kutu);
            window.draw(devamButon);
            window.draw(cikButon);
        }

};
int main(){
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "DENEME", sf::Style::None);
    sf::Vector2f windowsize(window.getSize().x, window.getSize().y);  
    Menu menu(windowsize);
    GameState state = GameState::Play;
    while(window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            };
            if(auto key = event->getIf<sf::Event::KeyPressed>()){
                if(key->code == sf::Keyboard::Key::Escape){
                    menu.toggle(state);
                }
            };
        }
        window.clear(sf::Color(64, 64, 64));
        if(state == GameState::Pause){
            menu.draw(window);
        }
        window.display(); 
    }
    return 0;
}