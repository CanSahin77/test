#include "game.h"

Game::Game():
    window(sf::VideoMode::getDesktopMode(), "Deneme", sf::Style::None),
    state(GameState::Play),
    menu(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)))
{
    window.setFramerateLimit(60);
}

void Game::run(){
    while(window.isOpen()){
        proccesEvent(); // ÖNCE OYUNUN ARKA PLANINDAKİ MANTIĞI YAP
        update(); // SONRA EKRANA ÇİZİLECEK OLAN ŞEYLERİ AYARLA
        render(); // EKRANA ÇİZ
        // BURADA FONKSİYONUN İÇİNE FONKSİYON ÇAĞRILARI YAZILIYOR BÖYLECE SADECE RUN FONKSİYONU MAİN DOSYASINDA ÇAĞIRILARAK
        // OYUN ÇALIŞTIRILABİLİYOR BURADAKİ OYUN ÇALIŞMA MANTIĞI SIRASI KOD YAZIM SIRASINA GÖREDİR
    }
}
void Game::proccesEvent(){
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
                sf::Vector2f mousepos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                
                if(menu.cikbutontiklama(mousepos)){
                    window.close();
                }else if(menu.dvbutontiklama(mousepos)){
                    state = GameState::Play;
                }
                // BURADA MOUSEGETPOSİTİON BİR İNTEGER DEĞER DÖDNRÜYÜORMUŞ O YÜZDEN FLOATA ÇEVİRMEMİZ GEREKİYOR
                // ÇÜNKÜ BELİRLEDİĞİMİZ BUTONLARIN SINIRLARI FLOAT İLE BELİRLENDİ
                // static cast kullanım şekli staticcast<hangi veri tipi lazım ise>(kullanacağımız fonksiyon);   
            }   
        }
    }
}
void Game::update(){
    if(state == GameState::Play){
        window.setMouseCursorVisible(0);
    }else if(state == GameState::Pause){
        window.setMouseCursorVisible(1);
    }
}

void Game::render(){
    window.clear(sf::Color(64, 64, 64));
        // BU ARADAKİ HER ŞEY EKRANA ÇİZİLECEK OLAN HER ŞEYİ İÇERİYOR
    if(state == GameState::Pause){
        menu.draw(window);
    }
         // BU ARADAKİ HER ŞEY EKRANA ÇİZİLECEK OLAN HER ŞEYİ İÇERİYOR
    window.display(); 
        // DİSPLAY UPDATE EDİYOR EKRANI
    
}