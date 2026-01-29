#pragma once
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(
        const sf::Texture& normal,
        const sf::Texture& hover,
        const sf::Texture& pressed
    );

    void setPosition(float x, float y);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    bool isClicked();
    void draw(sf::RenderWindow& window) const;

private:
    // le sprite du bouton qui aura la texture correspondant à son état
    sf::Sprite sprite;
    
    const sf::Texture* normalTexture;
    const sf::Texture* hoverTexture;
    const sf::Texture* pressedTexture;

    bool hovered = false;
    bool pressed = false;
    bool clicked = false;
};
