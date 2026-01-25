#include "menu.h"
#include "gamestate.h"

Menu::Menu(sf::Vector2f windowsize){
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
        // digital logicteki clock mantığı gibi her esc ye basıldığında state değişiyor
void Menu::toggle(GameState& state){
    if(state == GameState::Play){
        state = GameState::Pause;
    }else{
        state = GameState::Play;
    }
};
// BURADAKİ MANTIK MAİN KISMINDA SADECE MOUSE TIKLAMAYI KONTROL EDECEĞİZ EĞER MOUSE TIKLANDIYSA 
// BUTON TİKLAMA ÇAĞIRILIP DEVAM BUTONU SINIRLARI İÇERİSİNDE Mİ TIKLANDI ONU KONTROL EDECEĞİZ
bool Menu::dvbutontiklama(sf::Vector2f mousepos){
    return devamButon.getGlobalBounds().contains(mousepos);
}
bool Menu::cikbutontiklama(sf::Vector2f mousepos){
    return cikButon.getGlobalBounds().contains(mousepos);
}
//basitçe belirlediğimiz özellikleri ekrana çizme yeri
void Menu::draw(sf::RenderWindow& window){
    window.draw(ikinciKatman);
    window.draw(kutu);
    window.draw(devamButon);
    window.draw(cikButon);
}
