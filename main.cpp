#include <SFML/Graphics.hpp>
enum class GameState{
    Pause,
    Play
};
class Menu{
    public:
        void toggle(GameState& state){
            if(state == GameState::Play){
                state = GameState::Pause;
            }else{
                state = GameState::Play;
            }
        };

};
int main(){
    GameState state = GameState::Pause;
    Menu menu;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "DENEME", sf::Style::None);
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
        window.display(); 
    }
    return 0;
}