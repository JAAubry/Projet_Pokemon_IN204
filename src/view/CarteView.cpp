#include "view/CarteView.hpp"
#include <iostream>

CarteView::CarteView(sf::Texture& texture) {
    sprite.setTexture(texture);
}

void CarteView::set_position(float x, float y) {
    sprite.setPosition(x, y);
}

void CarteView::set_scale(float facteur) {
    sprite.setScale(facteur, facteur);
}

void CarteView::set_color(sf::Color couleur){
    sprite.setColor(couleur) ;
}

void CarteView::afficher(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool CarteView::is_hovered(sf::Vector2f position_souris){
    return sprite.getGlobalBounds().contains(position_souris) ;
}

bool CarteView::is_clicked(const sf::Event& event,const sf::RenderWindow& window){
    sf::Vector2i pixel_souris = sf::Mouse::getPosition(window);
    sf::Vector2f coord_souris = window.mapPixelToCoords(pixel_souris);
    if(is_hovered(coord_souris)) {
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left){
                std::cout << "Carte cliquée !" << std::endl;
                return true ;
        }
    }
    return false ;
}

