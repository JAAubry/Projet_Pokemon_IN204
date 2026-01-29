#include "ButtonView.hpp"
#include <iostream>

Button::Button(
    const sf::Texture& normal,
    const sf::Texture& hover,
    const sf::Texture& clicked
)
{
    normalTexture = &normal;
    hoverTexture = &hover;
    clickedTexture = &clicked;

    sprite.setTexture(*normalTexture);
}

void Button::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Button::setScale(float scale) {
    sprite.setScale(scale,scale);
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    clicked = false;

    sf::Vector2f PosSouris = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    hovered = sprite.getGlobalBounds().contains(PosSouris);

    if (hovered) {
        sprite.setTexture(*hoverTexture);

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            clicked = true;
            hovered = false;
        }
    }
    else {
        sprite.setTexture(*normalTexture);
        clicked = false;
    }
}

bool Button::isClicked() {
    return clicked;
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}
