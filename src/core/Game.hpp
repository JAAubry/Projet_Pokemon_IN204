#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "scene/Scene.hpp"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Font police;
    std::unique_ptr<Scene> currentScene;

    void changeToMenu();
    void changeToGame();
};
