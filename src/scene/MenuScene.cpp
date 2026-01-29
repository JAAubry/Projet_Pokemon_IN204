#include "MenuScene.hpp"

MenuScene::MenuScene(sf::Font& police) {
    texte.setFont(police);
    texte.setString("Scene: MENU\nPress Enter");
    texte.setCharacterSize(40);
    texte.setPosition(400, 300);
}

void MenuScene::handleEvent(const sf::Event&,sf::RenderWindow& window) {}
void MenuScene::update(float) {}

void MenuScene::draw(sf::RenderWindow& window) {
    window.draw(texte);
}
