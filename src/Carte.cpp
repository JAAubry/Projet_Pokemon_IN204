#include "carte.hpp"

// Constructeur par défaut
Carte::Carte() : nom("Inconnue"), pointsDeVie(0), degatsAttaque(0) {}

// Constructeur avec paramètres
Carte::Carte(const std::string& nom, int pv, int degats)
    : nom(nom), pointsDeVie(pv), degatsAttaque(degats) {}

// Getters
std::string Carte::getNom() const {
    return nom;
}

int Carte::getPointsDeVie() const {
    return pointsDeVie;
}

int Carte::getDegatsAttaque() const {
    return degatsAttaque;
}

// Méthodes
void Carte::subirDegats(int degats) {
    pointsDeVie -= degats;
    if (pointsDeVie < 0) {
        pointsDeVie = 0;
    }
}

bool Carte::estK.O() const {
    return pointsDeVie <= 0;
}
