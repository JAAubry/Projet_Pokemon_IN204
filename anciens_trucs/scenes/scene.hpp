#include <SFML/Graphics.hpp>
#include "graphics/ui/bouton.hpp"
#include "graphics/ui/zones.hpp"
// Manque les headers de controller

// Classe abstraite
class Scene { 
protected : 
    virtual ~Scene() = default;
    virtual void gererEvent(sf::Event& event) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void dessiner(sf::RenderWindow& window) = 0;
};

class SceneCombat : public Scene {
private:
    GameState& game;
    GameController& controller;

    // UI
    Bouton BoutonFinTour;
    std::vector<Bouton> BoutonsMain;

    // Graphisme
    sf::Sprite background;
    sf::Font font;
    sf::Text hpText;

    // Sélection
    int selectedCard = -1;
};

// TO DO Ajouter écran victoire/défaite
