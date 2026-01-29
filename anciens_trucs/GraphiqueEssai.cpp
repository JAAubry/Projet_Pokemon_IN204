#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // Backround
    sf::Texture textureFond;
    textureFond.loadFromFile("fond_pokemon.jpg");
    sf::Sprite fond(textureFond);
    sf::Vector2u tailleFenetre = window.getSize();
    sf::Vector2u tailleTexture = textureFond.getSize();
    float scaleX = static_cast<float>(tailleFenetre.x) / tailleTexture.x;
    float scaleY = static_cast<float>(tailleFenetre.y) / tailleTexture.y;
    fond.setScale(scaleX, scaleY);
    std::cout << tailleFenetre.x << std::endl ;
    std::cout << tailleFenetre.y << std::endl ;

    // Placeholder sprites cartes du banc et active
    sf::Texture textureDosCarte ;
    textureDosCarte.loadFromFile("dos_carte.jpg");
    sf::Sprite carteActive(textureDosCarte) ;
    carteActive.setScale(0.1, 0.1);
    sf::Sprite carteBanc1(carteActive) ;
    sf::Sprite carteBanc2(carteActive) ;
    sf::Sprite carteBanc3(carteActive) ;

    // Position
    carteActive.setPosition(sf::Vector2f(380,350)) ;
    carteBanc1.setPosition(sf::Vector2f(500, 400));
    carteBanc2.setPosition(sf::Vector2f(600, 400));
    carteBanc3.setPosition(sf::Vector2f(700, 400));



    while (window.isOpen())
    {
        sf::Event event;
        // vérification des events
        while (window.pollEvent(event))
        { 
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        std::cout << "x=" << mousePos.x << " y=" << mousePos.y << "\r";

        

        window.clear(sf::Color::Black);
        window.draw(fond) ;
        window.draw(carteActive) ;
        window.draw(carteBanc1) ;
        window.draw(carteBanc2) ;
        window.draw(carteBanc3) ;
        window.display();
    }
}
