#include "GameScene.hpp"
#include "view/ButtonView.hpp"
#include <iostream>

// =================================================
// CONSTRUCTEUR
// =================================================
GameScene::GameScene(sf::Font& police,sf::RenderWindow& window) {

    // Init des champs
    this->windowSize= window.getSize();
    if (!carteTexture.loadFromFile("assets/textures/dos_carte.jpg")) {
    std::cerr << "Erreur chargement dos_carte.jpg\n";
    }
    if (!piocherTexture.loadFromFile("assets/textures/PIOCHER.png")) {
    std::cerr << "Erreur chargement PIOCHER.png\n";
    }
    // if (!retraitTexture.loadFromFile("assets/textures/RETRAIT.png")) {
    // std::cerr << "Erreur chargement RETRAIT.png\n";
    // }

    // ===== CARTE ACTIVE =====
    // Joueur actif
    this->carteActive = CarteView(carteTexture);
    carteActive.set_scale(0.14f);
    carteActive.set_position(
        windowSize.x/2 + 250.f
        , windowSize.y/2 + 185.f);
    // Joueur adversaire
    this->carteActive_adversaire = CarteView(carteTexture);
    carteActive_adversaire.set_scale(0.14f);
    carteActive_adversaire.set_position(
        windowSize.x/2 - 365.f
        , windowSize.y/2 - 185.f - 165.f);


    // ===== BANC (3 cartes) =====
    // Joueur actif
    for (int i = 0; i < 3; ++i) {
        CarteView carte(carteTexture);
        carte.set_scale(0.12f);
        carte.set_position(
            windowSize.x/2 + 150.f + i * 110.f,
            windowSize.y/2 + 20.f
        );
        banc.push_back(carte);
    }
    // Joueur adversaire
    for (int i = 0; i < 3; ++i) {
        CarteView carte(carteTexture);
        carte.set_scale(0.12f);
        carte.set_position(
            windowSize.x/2 - 250.f - i * 110.f,
            windowSize.y/2 - 140.f - 20.f
        );
        banc_adversaire.push_back(carte);
    }
    

    // ===== MAIN (7 cartes) =====
    for (int i = 0; i < 7; ++i) {
        CarteView carte(carteTexture);
        carte.set_scale(0.1f);
        carte.set_position(
            20.f + i * 90.f,
            windowSize.y - 250.f
        );
        main.push_back(carte);
    }

    // ============ FOND ============
    if (!backgroundTexture.loadFromFile("assets/textures/fond_pokemon.jpg")) {
        std::cerr << "Erreur chargement fond\n";
    }
    backgroundSprite.setTexture(backgroundTexture);
    // Adapter le fond à la taille de la fenêtre 
    float scaleX = float(windowSize.x) / backgroundTexture.getSize().x;
    float scaleY = float(windowSize.y) / backgroundTexture.getSize().y;
    // on prend le max pour que le fond remplisse toute la fenêtre
    float scale = std::max(scaleX, scaleY);
    backgroundSprite.setScale(scale, scale);
    sf::FloatRect spriteBounds = backgroundSprite.getGlobalBounds();
    backgroundSprite.setPosition(
    (windowSize.x - spriteBounds.width) / 2.f,
    (windowSize.y - spriteBounds.height) / 2.f
    ) ;

    // ==== TEXTE ====
    texte.setFont(police);
    texte.setString("Score du joueur 1 : x/3 \nScore du joueur 2 : x/3") ;
    texte.setPosition(
        windowSize.x/2,
        windowSize.y/20
    ) ;

    // ==== BOUTON PIOCHER====
    this->piocher = Button(piocherTexture,piocherTexture,piocherTexture) ;
    piocher.setScale(0.05) ;
    piocher.setPosition(
        windowSize.x/2 - 350.f,
        windowSize.y*9/10
    ) ;

    // ==== BOUTON RETRAIT ====
    // this->retrait = Button(retraitTexture,retraitTexture,retraitTexture) ;
    // retrait.setScale(0.05) ;
    // retrait.setPosition(
    //     windowSize.x/2 - 240.f,
    //     windowSize.y*9/10
    // ) ;

}





// =================================================
// HANDLE EVENT
// =================================================

void GameScene::handleEvent(const sf::Event& event,sf::RenderWindow& window) {
    piocher.handleEvent(event, window) ;
    //retrait.handleEvent(event,window);

    // if(retrait.isClicked()){
    //     retreatActiveCard() ;
    // }

    // main
    for (size_t i = 0; i < main.size(); ++i) {
        CarteView& carte = main[i];
        if (carte.is_clicked(event,window)) {
            playCardFromHand(i) ;
        }
    }

    // banc
    for (size_t i = 0; i < banc.size(); ++i) {
        CarteView& carte = banc[i];
        if (carte.is_clicked(event,window)) {
            playCardFromBench(i) ;
        }
    }  
}


// =========== UPDATE =============

void GameScene::update(float dt) {
    // Mettre à jour les animations en cours
    for (auto& anim : animations) {
        anim.update(dt);
    }

    // Ajouter les cartes terminées dans le banc et supprimer l'animation
    auto it = animations.begin();
    while (it != animations.end()) {
        if (it->finished) {
            CarteView carte = it->carte;
            carte.set_position(it->targetPos.x,it->targetPos.y);
            carte.set_scale(it->targetScale);
            banc.push_back(carte);
            it = animations.erase(it);
        }
        else {
            ++it;
        }
    }
}




// ========== DRAW ============

void GameScene::draw(sf::RenderWindow& window) {
    //std::cout << "Souris : (" << sf::Mouse::getPosition(window).x << ", " << sf::Mouse::getPosition(window).y << ")\n";

    window.draw(backgroundSprite) ;
    window.draw(texte);

    piocher.draw(window);
    //retrait.draw(window);

    carteActive.afficher(window);
    carteActive_adversaire.afficher(window);
    

    for (auto& carte : banc){
        carte.afficher(window);
    }      

    for (auto& carte : banc_adversaire){
        carte.afficher(window);
    }

    for (auto& carte : main){
        carte.afficher(window);
    }

    for (auto& anim : animations) {
        anim.draw(window);
    }

}

// ===== AUTRES FONCTIONS

void GameScene::playCardFromHand(size_t index) {
    if (index >= main.size()) return;

    CarteView& carte = main[index];

    // Calculer position libre dans le banc
    sf::Vector2f target(
        windowSize.x/2.f + 150.f + banc.size() * 110.f,
        windowSize.y/2.f + 20.f
    );

    // Ajouter animation
    animations.emplace_back(carte, target,0.12f);

    // Retirer la carte de la main
    main.erase(main.begin() + index);
}



void GameScene::playCardFromBench(size_t index) {
    if (index >= banc.size()) return;

    CarteView& carte = banc[index];   
    sf::Vector2f target(
        windowSize.x/2 + 250.f
        , windowSize.y/2 + 185.f);

    // Ajouter animation
    animations.emplace_back(carte, target,0.14f);

    // Retirer la carte de la main
    banc.erase(banc.begin() + index);
}


// TO DO retraite 

// void GameScene::retreatActiveCard() {
//     std::cout << "dans retreat" << std::endl ;
//     // Sécurité : banc plein
//     if (banc.size() >= 3)
//         return;

//     // Position cible sur le banc
//     sf::Vector2f target(
//         windowSize.x / 2.f + 150.f + banc.size() * 110.f,
//         windowSize.y / 2.f + 20.f
//     );

//     // Lancer l’animation depuis la carte active
//     animations.emplace_back(
//         carteActive,
//         target,
//         0.12f   // scale normale d'une carte de banc
//     );

//     // Remplacer la carte active par une carte "vide"
//     carteActive = CarteView(carteTexture);
//     carteActive.set_scale(0.14f);
//     carteActive.set_position(
//         windowSize.x / 2.f + 250.f,
//         windowSize.y / 2.f + 185.f
//     );
// }






