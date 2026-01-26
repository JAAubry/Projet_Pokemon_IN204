#include "carte.hpp"

// ------------------
// CONSTRUCTEURS
// ------------------

// Carte vide / inactive
Carte::Carte()
    : nom(""), pointsDeVie(0), pointsDeVieMax(0), degatsAttaque(0), energieRetraite(0), energieAttaque(0), energieAttachee(0){}

// Carte Pokémon
Carte::Carte(const std::string& nom, int pv, int pvmax int degats, int energieR, int coutAttaque)
    : nom(nom), pointsDeVie(pv), pointsDeVieMax(pvmax), degatsAttaque(degats), energieRetraite(energieR), energieAttaque(coutAttaque), energieAttachee(0) {}

// ------------------
// EEXTRACTEUR
// ------------------
const std::string& Carte::getNom() const {
    return nom;
}

int Carte::getPointsDeVie() const {
    return pointsDeVie;
}

int Carte::getPointsDeVieMax() const {
    return pointsDeVieMax;
}

int Carte::getDegatsAttaque() const {
    return degatsAttaque;
}
int Carte::getEnergieRetraite() const {
    return energieRetraite;
}
int Carte::getEnergieAttaque() const{
    return energieAttaque;
}
int Carte::getEnergieAttachee() const{
    return energieAttachee;
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
//-------------------
//ENERGIE
//-------------------

void Carte::ajouterEnergie(int quantite) {
    if (quantite > 0) {
        energieAttachee += quantite;
    }
}

bool Carte::peutAttaquer() const {
    return estValide() && energieAttachee >= energieAttaque;
}

bool Carte::peutBattreEnRetraite() const {
    return estValide() && energieAttachee >= energieRetraite;
}

void Carte::battreEnRetraite() {
    if (peutBattreEnRetraite()) {
        energieAttachee -= energieRetraite;
    }
}

void Carte::soigner(int pv) {
    if (pv > 0 && !estKO()) {
        pointsDeVie = std::min(pointsDeVie + pv, pointDeVieMax);
    }
}


