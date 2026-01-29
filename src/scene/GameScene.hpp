#pragma once
#include "Scene.hpp"
#include "view/CarteView.hpp"
#include "view/ButtonView.hpp"
#include "view/AnimationCarte.hpp"
#include <SFML/Graphics.hpp>
#include <view/CarteView.hpp>


class GameScene : public Scene {
public:
    GameScene(sf::Font& police,sf::RenderWindow& window);

    void handleEvent(const sf::Event& event,sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    void playCardFromHand(size_t index);
    void playCardFromBench(size_t index);
    // void retreatActiveCard();

private:
    // OPTION D'APPROFONDISSEMENT : ajouter un requirement que ca s'ouvre bien
    // Definition des textures, elles doivent exister plus longtemps que les sprites    
    sf::Text texte;
    sf::Texture carteTexture; 
    sf::Texture backgroundTexture;
    sf::Texture piocherTexture;
    sf::Texture retraitTexture;

    sf::Sprite backgroundSprite ;

    // Cartes
    CarteView carteActive;
    std::vector<CarteView> banc;
    std::vector<CarteView> main;
    CarteView carteActive_adversaire;
    std::vector<CarteView> banc_adversaire;
    Button piocher ;
    //Button retrait ;

    // Pour animations
    std::vector<AnimationCarte> animations;
    sf::Vector2u windowSize;
};
