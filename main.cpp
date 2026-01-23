#include <SFML/Graphics.hpp>
enum class GameState{
    Pause,
    Play
};
class Menu{
    // default constructor yazmadım yani
    // Menu a;
    // böyle bir nesne oluşturulamaz,
    // Menu a(windowsize) buna ihtiyacı var ben yazmak istemedim default constructor
    private:
        //ikinci katman yarı saydam oyun görünmeye devam etsin diye var kutu ise menünün sınırları 
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
        // digital logicteki clock mantığı gibi her esc ye basıldığında state değişiyor
        void toggle(GameState& state){
            if(state == GameState::Play){
                state = GameState::Pause;
            }else{
                state = GameState::Play;
            }
        };
        // BURADAKİ MANTIK MAİN KISMINDA SADECE MOUSE TIKLAMAYI KONTROL EDECEĞİZ EĞER MOUSE TIKLANDIYSA 
        // BUTON TİKLAMA ÇAĞIRILIP DEVAM BUTONU SINIRLARI İÇERİSİNDE Mİ TIKLANDI ONU KONTROL EDECEĞİZ
        bool dvbutontiklama(sf::Vector2f mousepos){
            return devamButon.getGlobalBounds().contains(mousepos);
        }
        bool cikbutontiklama(sf::Vector2f mousepos){
            return cikButon.getGlobalBounds().contains(mousepos);
        }
        //basitçe belirlediğimiz özellikleri ekrana çizme yeri
        void draw(sf::RenderWindow& window){
            window.draw(ikinciKatman);
            window.draw(kutu);
            window.draw(devamButon);
            window.draw(cikButon);
        }

};
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