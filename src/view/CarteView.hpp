#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class CarteView {
private:
    sf::Sprite sprite;

public:
    // L'utilisateur n'utilise pas le constructeur par défaut, c'est pour les constructeurs de GameScene
    CarteView() = default; 
    CarteView(sf::Texture& texture);
    CarteView(const CarteView& other): sprite(other.sprite){}

    void set_position(float x, float y);
    void set_scale(float facteur);
    void set_color(sf::Color couleur) ;
    void afficher(sf::RenderWindow& window);

    // Reaction events
    bool is_hovered(sf::Vector2f position_souris);
    bool is_clicked(const sf::Event& event,const sf::RenderWindow& window);

};
