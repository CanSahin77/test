#include <SFML/Graphics.hpp>
#include "menu.h"
#include "gamestate.h"
int main(){
    // pencere açma yeri videomode getdesktopmode fullscreen olması için style none ise windowed fullscreen olmasın diye
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "DENEME", sf::Style::None);
    // pencere ekran büyüklüğünü alma
    sf::Vector2f windowsize(window.getSize().x, window.getSize().y);  
    //menü nesnesi oluşturuldu
    Menu menu(windowsize);
    // oyuna başladığımızda oynanır halde başlasın ya da pause yani menü açık şekilde başlasın
    GameState state = GameState::Play;
    // pencere açık iken
    while(window.isOpen()){
        // sıradaki eventi yakalama yeri keypressed closed mousepressed yani oyunu oynamamzı için kontrol etmemiz gereken
        // şeyleri yakalamak için event kullanılıyor
        while(auto event = window.pollEvent()){
            // buradaki event->is eventi pointerla is gösteriyoruz is sadece doğru mu değil mi onu kontrol ediyor
            // neden pointer kullanıldığını bilmiyorum. "sen bunu araştır yardım et volkan"
            if(event->is<sf::Event::Closed>()){
                window.close();
            };
            // buradaki getif in isden farkı is sadece doğru mu ya da var mı diyor getif varsa eğer getir yoksa siktir et
            if(auto key = event->getIf<sf::Event::KeyPressed>()){
                if(key->code == sf::Keyboard::Key::Escape){
                    menu.toggle(state);
                }
            };
                if(state == GameState::Pause){
                    window.setMouseCursorVisible(1);
                    if(auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()){
                        // BURADA MOUSEGETPOSİTİON BİR İNTEGER DEĞER DÖDNRÜYÜORMUŞ O YÜZDEN FLOATA ÇEVİRMEMİZ GEREKİYOR
                        // ÇÜNKÜ BELİRLEDİĞİMİZ BUTONLARIN SINIRLARI FLOAT İLE BELİRLENDİ
                        // static cast kullanım şekli staticcast<hangi veri tipi lazım ise>(kullanacağımız fonksiyon);
                        sf::Vector2f mousepos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                        
                        if(menu.cikbutontiklama(mousepos)){
                            window.close();
                        }else if(menu.dvbutontiklama(mousepos)){
                            state = GameState::Play;
                        }
                    }
                }
                if(state == GameState::Play){
                    window.setMouseCursorVisible(0);
                }
        }
        window.clear(sf::Color(64, 64, 64));
        // BU ARADAKİ HER ŞEY EKRANA ÇİZİLECEK OLAN HER ŞEYİ İÇERİYOR
        if(state == GameState::Pause){
            menu.draw(window);
        }
         // BU ARADAKİ HER ŞEY EKRANA ÇİZİLECEK OLAN HER ŞEYİ İÇERİYOR
        window.display(); 
        // DİSPLAY UPDATE EDİYOR EKRANI
    }
    return 0;
}