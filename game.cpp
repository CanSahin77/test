#include "game.h"
#include <algorithm>
Game::Game():
    window(sf::VideoMode::getDesktopMode(), "Deneme", sf::Style::None),
    state(GameState::Play),
    menu(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y))),
    player(window)
{
    window.setFramerateLimit(60);
}
void Game::spawnObstacle(){
    float x = window.getSize().x + 200.f;
    float y = 0.f;
    obstacles.emplace_back(sf::Vector2f(x, y));
}

void Game::run(){
    while(window.isOpen()){
        delta = clock.restart().asSeconds();
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
        }else if(state == GameState::Play){
            if(auto key = event->getIf<sf::Event::KeyPressed>()){
                if(key->code == sf::Keyboard::Key::Space){
                    player.jump();
                }
            }
        }
    }
}
void Game::update(){
    if(state == GameState::Play){
        window.setMouseCursorVisible(false);
        player.update(delta);

        if(spawnClock.getElapsedTime().asSeconds() > 2.0f){
            spawnObstacle();
            spawnClock.restart();
        }

        for(auto& obs : obstacles){
            obs.update(delta, obstacleSpeed);

            if (obs.getBounds().findIntersection(player.getBounds())){
                state = GameState::GameOver;
            }
        }

        // Ekran dışı boruları sil
        obstacles.erase(
            std::remove_if(obstacles.begin(), obstacles.end(),
                [](Obstacle& o){
                    return o.getBounds().position.x + o.getBounds().size.x < 0;
                }),
            obstacles.end()
        );
    }
    else if(state == GameState::Pause){
        window.setMouseCursorVisible(true);
    }
}


void Game::render(){
    window.clear(sf::Color(64,64,64));

    if(state == GameState::Play){
        for(auto& obs : obstacles)
            obs.draw(window);

        player.draw(window);
    }

    if(state == GameState::Pause){
        menu.draw(window);
    }

    window.display();
}
