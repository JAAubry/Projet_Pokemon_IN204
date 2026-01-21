#include "carte.hpp"

// ------------------
// CONSTRUCTEURS
// ------------------

// Carte vide / inactive
Carte::Carte()
    : nom(""), pointsDeVie(0), degatsAttaque(0) {}

// Carte Pokémon
Carte::Carte(const std::string& nom, int pv, int degats, int energieR, int enerieA)
    : nom(nom), pointsDeVie(pv), degatsAttaque(degats), energieRetraite(energieR), energieAttaque(EnergieA) {}

// ------------------
// EEXTRACTEUR
// ------------------
const std::string& Carte::getNom() const {
    return nom;
}

int Carte::getPointsDeVie() const {
    return pointsDeVie;
}

int Carte::getDegatsAttaque() const {
    return degatsAttaque;
}
int Carte::getEnergieRetraite() const {
    return energieRetraite;
}
int Carte::getEnerieAttaque() const{
    return energieAttaque;
}

// ------------------
// ÉTAT
// ------------------
bool Carte::estKO() const {
    return pointsDeVie <= 0;
}

bool Carte::estValide() const {
    return !nom.empty() && !estKO();
}

// ------------------
// COMBAT
// ------------------
void Carte::subirDegats(int degats) {
    if (degats < 0) return;

    pointsDeVie -= degats;
    if (pointsDeVie < 0) {
        pointsDeVie = 0;
    }
}
