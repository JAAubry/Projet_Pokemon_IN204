#include "CarteDresseur.hpp"
#include "Joueur.hpp"
#include <iostream>

CarteDresseur::CarteDresseur(const std::string& nom,
                             const std::string& effet,
                             TypeDresseur type)
    : nom(nom), effet(effet), type(type) {}

TypeCarte CarteDresseur::getType() const {
    return TypeCarte::Dresseur;
}

const std::string& CarteDresseur::getNom() const {
    return nom;
}

TypeDresseur CarteDresseur::getTypeDresseur() const {
    return type;
}

void CarteDresseur::appliquerEffet(Joueur& joueur) {
    std::cout << joueur.getNom()
              << " joue " << nom << std::endl;

    if (nom == "Potion") {
        joueur.soignerCarteActive(20);
    } else if (nom == "Recherche") {
        joueur.piocher(2);
        joueur.marquerSupporterJoue();
    }
}
