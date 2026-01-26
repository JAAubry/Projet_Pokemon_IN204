#include "dresseur.hpp"
#include "joueur.hpp"
#include <iostream>

// ------------------
// Constructeurs
// ------------------
Dresseur::Dresseur()
    : nom(""), type(TypeDresseur::Objet) {}

Dresseur::Dresseur(const std::string& nom, const std::string& description, TypeDresseur type)
    : nom(nom), description(description), type(type) {}

// ------------------
// Getters
// ------------------
const std::string& Dresseur::getNom() const {
    return nom;
}

const std::string& Dresseur::getDescription() const {
    return description;
}

TypeDresseur Dresseur::getType() const {
    return type;
}

// ------------------
// Vérification
// ------------------
bool Dresseur::peutEtreJoue(const Joueur& joueur) const {
    // Exemple de règles simples
    if (type == TypeDresseur::Supporter) {
        return !joueur.getSupporterDejaJoue();
    }

    // Objet : toujours jouable
    return true;
}

// ------------------
// Effets
// ------------------
void Dresseur::appliquerEffet(Joueur& joueur) const {
    std::cout << joueur.getNom()
              << " joue la carte Dresseur : "
              << nom << std::endl;

    // ------------------
    // OBJETS
    // ------------------
    if (nom == "Potion") {
        if (joueur.aCarteActive()) {
            joueur.soignerCarteActive(20);
            std::cout << "La carte active récupère 20 PV." << std::endl;
        }
    }
    else if (nom == "Super Potion") {
        if (joueur.aCarteActive()) {
            joueur.soignerCarteActive(40);
            std::cout << "La carte active récupère 40 PV." << std::endl;
        }
    }

    // ------------------
    // SUPPORTERS
    // ------------------
    else if (nom == "Recherche Professeur") {
        joueur.piocher(2);
        joueur.marquerSupporterJoue();
        std::cout << joueur.getNom() << " pioche 2 cartes." << std::endl;
    }

    else {
        std::cout << "Effet de la carte non implémenté." << std::endl;
    }
}
