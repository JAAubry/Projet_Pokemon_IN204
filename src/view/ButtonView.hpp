#pragma once
#include <SFML/Graphics.hpp>

class Button {
public:
    Button() = default ;
    Button(
        const sf::Texture& normal,
        const sf::Texture& hover,
        const sf::Texture& clicked
    );

    void setPosition(float x, float y);
    void setScale(float scale);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    bool isClicked();
    void draw(sf::RenderWindow& window) const;

private:
    // le sprite du bouton qui aura la texture correspondant à son état
    sf::Sprite sprite;
    
    const sf::Texture* normalTexture;
    const sf::Texture* hoverTexture;
    const sf::Texture* clickedTexture;

    bool hovered = false;
    bool clicked = false;
};
