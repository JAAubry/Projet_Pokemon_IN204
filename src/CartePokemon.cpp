#include "CartePokemon.hpp"
#include <iostream>
#include <algorithm>

CartePokemon::CartePokemon(const std::string& nom, const std::string& type,
                           int pv, int degats, int coutAttaque, int coutRetraite,
                           const std::string& faiblesse)
    : nom(nom),
      type(type),
      pvMax(pv),
      pv(pv),
      degats(degats),
      energie(0),
      coutAttaque(coutAttaque),
      coutRetraite(coutRetraite),
      faiblesse(faiblesse) {}

TypeCarte CartePokemon::getType() const {
    return TypeCarte::Pokemon;
}

const std::string& CartePokemon::getNom() const {
    return nom;
}

const std::string& CartePokemon::getTypeElementaire() const {
    return type;
}

const std::string& CartePokemon::getFaiblesse() const {
    return faiblesse;
}

int CartePokemon::getPV() const {
    return pv;
}

int CartePokemon::getPVMax() const {
    return pvMax;
}

int CartePokemon::getEnergie() const {
    return energie;
}

int CartePokemon::getCoutRetraite() const {
    return coutRetraite;
}

bool CartePokemon::estKO() const {
    return pv <= 0;
}

bool CartePokemon::peutAttaquer() const {
    return energie >= coutAttaque && !estKO();
}

bool CartePokemon::peutRetraite() const {
    return energie >= coutRetraite && !estKO();
}

void CartePokemon::attaquer(CartePokemon& cible) {
    if (!peutAttaquer()) {
        std::cout << nom << " n'a pas assez d'énergie pour attaquer!\n";
        return;
    }

    int degatsInfliges = degats;
    
    // Vérifier la faiblesse
    if (!cible.faiblesse.empty() && type == cible.faiblesse) {
        degatsInfliges *= 2;
        std::cout << "C'est super efficace! (x2 dégâts)\n";
    }

    cible.recevoirDegats(degatsInfliges);
    
    std::cout << nom << " attaque " << cible.nom 
              << " et inflige " << degatsInfliges << " dégâts!\n";
}

void CartePokemon::recevoirDegats(int montant) {
    pv -= montant;
    if (pv < 0) pv = 0;
    
    if (estKO()) {
        std::cout << nom << " est K.O.!\n";
    }
}

void CartePokemon::ajouterEnergie(int qte) {
    energie += qte;
    std::cout << nom << " reçoit " << qte << " énergie(s). "
              << "Total: " << energie << "\n";
}

void CartePokemon::payerRetraite() {
    if (!peutRetraite()) {
        std::cout << nom << " n'a pas assez d'énergie pour battre en retraite!\n";
        return;
    }
    
    energie -= coutRetraite;
    std::cout << nom << " bat en retraite (coût: " << coutRetraite << " énergie)\n";
}

void CartePokemon::soigner(int montant) {
    if (estKO()) {
        std::cout << nom << " est K.O. et ne peut pas être soigné!\n";
        return;
    }
    
    int anciensPV = pv;
    pv = std::min(pv + montant, pvMax);
    int pvSoignes = pv - anciensPV;
    
    std::cout << nom << " est soigné de " << pvSoignes << " PV. "
              << "PV actuels: " << pv << "/" << pvMax << "\n";
}

void CartePokemon::afficher() const {
    std::cout << nom << " [" << type << "]"
              << " (PV: " << pv << "/" << pvMax
              << ", Energie: " << energie
              << ", Attaque: " << coutAttaque
              << ", Retraite: " << coutRetraite << ")\n";
}
