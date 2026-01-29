#include "bouton.hpp"

Button::Button(
    const sf::Texture& normal,
    const sf::Texture& hover,
    const sf::Texture& pressed
)
{
    normalTexture = &normal;
    hoverTexture = &hover;
    pressedTexture = &pressed;

    sprite.setTexture(*normalTexture);
}

void Button::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    clicked = false;

    sf::Vector2f PosSouris = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    hovered = sprite.getGlobalBounds().contains(mousePos);

    if (hovered) {
        sprite.setTexture(*hoverTexture);

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            pressed = true;
            sprite.setTexture(*pressedTexture);
        }

        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left &&
            pressed)
        {
            clicked = true;
            pressed = false;
        }
    }
    else {
        sprite.setTexture(*normalTexture);
        pressed = false;
    }
}

bool Button::isClicked() {
    return clicked;
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}
