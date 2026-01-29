#include "Game.hpp"
#include "scene/MenuScene.hpp"
#include "scene/GameScene.hpp"

Game::Game() :
    window(sf::VideoMode(1280, 720), "Pokemon TCG") {

    police.loadFromFile("assets/fonts/PokemonSolid.ttf");
    changeToMenu();
}

void Game::run() {
    // c'est pour update
    sf::Clock horloge;

    while (window.isOpen()) {
        float dt = horloge.restart().asSeconds();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter)
                    changeToGame();
                if (event.key.code == sf::Keyboard::Escape)
                    changeToMenu();
            }

            currentScene->handleEvent(event,window);
        }

        currentScene->update(dt);

        window.clear();
        currentScene->draw(window);
        window.display();
    }
}

void Game::changeToMenu() {
    currentScene = std::make_unique<MenuScene>(police);
}

void Game::changeToGame() {
    currentScene = std::make_unique<GameScene>(police,window);
}
