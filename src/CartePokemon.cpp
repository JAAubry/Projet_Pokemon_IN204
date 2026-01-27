#include "CartePokemon.hpp"
#include <iostream>

CartePokemon::CartePokemon(const std::string& nom,
                           int pv,
                           int degats,
                           int retraite,
                           int coutAttaque)
    : nom(nom),
      pointsDeVie(pv),
      degats(degats),
      energieAttachee(0),
      coutAttaque(coutAttaque),
      coutRetraite(retraite) {}

TypeCarte CartePokemon::getType() const {
    return TypeCarte::Pokemon;
}

const std::string& CartePokemon::getNom() const {
    return nom;
}

bool CartePokemon::estKO() const {
    return pointsDeVie <= 0;
}

bool CartePokemon::peutAttaquer() const {
    return !estKO() && energieAttachee >= coutAttaque;
}

void CartePokemon::attaquer(CartePokemon& cible) {
    if (!peutAttaquer()) return;
    cible.subirDegats(degats);
}

void CartePokemon::subirDegats(int d) {
    pointsDeVie -= d;
    if (pointsDeVie < 0) pointsDeVie = 0;
}

void CartePokemon::ajouterEnergie(int n) {
    energieAttachee += n;
}

bool CartePokemon::peutBattreEnRetraite() const {
    return energieAttachee >= coutRetraite;
}

void CartePokemon::battreEnRetraite() {
    if (peutBattreEnRetraite()) {
        energieAttachee -= coutRetraite;
    }
}

void CartePokemon::afficher() const {
    std::cout << nom
              << " | PV: " << pointsDeVie
              << " | Energie: " << energieAttachee
              << std::endl;
}
