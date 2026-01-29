#pragma once
#include "CarteView.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class AnimationCarte {
    public : 
    CarteView carte;           
    sf::Vector2f targetPos;  
    float targetScale;  
    float zoomFactor = 0.4f;   
    float duration = 0.3f;     
    float elapsed = 0.f;       
    bool finished = false;

    AnimationCarte(const CarteView& c, const sf::Vector2f& pos, float scl): 
    carte(c), targetPos(pos), targetScale(scl) {
        carte = CarteView(c) ;
        carte.set_position(500.f,200.f);
        targetPos = pos ;
        targetScale =scl ;
    }

    void update(float dt) {
        if (finished) return;

        elapsed += dt;
        float t = std::min(elapsed/duration, 1.f);

        // Zoom linéaire
        float scale = 0.2 + t * (zoomFactor - 0.2);
        carte.set_scale(scale);

        // Clignotement alpha rétro
        float alpha = 255.f * (0.5f + 0.5f * std::sin(elapsed*20.f));
        carte.set_color(sf::Color(255,255,255, static_cast<sf::Uint8>(alpha)));

        if (t >= 1.f) {
            finished = true;
            carte.set_scale(targetScale);
            carte.set_color(sf::Color::White);
            carte.set_position(targetPos.x,targetPos.y);
        }
    }

    void draw(sf::RenderWindow& window) {
        carte.afficher(window);
    }
};
