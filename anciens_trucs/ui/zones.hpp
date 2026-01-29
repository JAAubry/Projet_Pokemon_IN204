#pragma once
#include <SFML/Graphics.hpp>

class Zone {
    public:
    float largeurcarte;
    float espace;    
    sf::FloatRect aire; //{x en haut à gauche,y en haut à gauche,largeur,hauteur}

    Zone(float l,float e, sf::FloatRect r) : largeurcarte(l),espace(e), rectlg(r) {}
  
    // positions de cartes bien espacées pour count cartes
    std::vector<sf::Vector2f> calculPositionCarte(size_t count) ;
};




