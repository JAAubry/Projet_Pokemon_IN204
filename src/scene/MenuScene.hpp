#pragma once
#include "Scene.hpp"
#include <SFML/Graphics.hpp>

class MenuScene : public Scene {
public:
    MenuScene(sf::Font& police);

    void handleEvent(const sf::Event& event,sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Text texte;
};
