#include "CarteDresseur.hpp"
#include "Joueur.hpp"
#include <iostream>

CarteDresseur::CarteDresseur(const std::string& nom, TypeDresseur type)
    : nom(nom), type(type) {}

TypeCarte CarteDresseur::getType() const {
    return TypeCarte::Dresseur;
}

const std::string& CarteDresseur::getNom() const {
    return nom;
}

TypeDresseur CarteDresseur::getSousType() const {
    return type;
}

void CarteDresseur::appliquerEffet(Joueur& joueur) {
    std::cout << joueur.getNom() << " joue " << nom << "\n";

    // Cartes Item (Objet)
    if (nom == "Potion") {
        joueur.soignerActif(20);
    }
    else if (nom == "X Speed") {
        std::cout << "Le coût de retraite est réduit de 1 ce tour.\n";
        // Cet effet nécessiterait un système de buffs temporaires
    }
    else if (nom == "Hand Scope") {
        std::cout << "Vous pouvez voir la main de l'adversaire.\n";
        // Nécessite l'accès à l'adversaire
    }
    else if (nom == "Pokedex") {
        std::cout << "Vous regardez les 3 premières cartes de votre deck.\n";
        joueur.voirTopDeck(3);
    }
    else if (nom == "Poke Ball") {
        std::cout << "Vous cherchez un Pokémon de base dans votre deck.\n";
        // Nécessite un système de recherche dans le deck
    }
    else if (nom == "Red Card") {
        std::cout << "L'adversaire mélange sa main dans son deck et pioche 3 cartes.\n";
        // Nécessite l'accès à l'adversaire
    }
    
    // Cartes Supporter
    else if (nom == "Professor's Research" || nom == "Recherche") {
        joueur.piocher(2);
    }
    else if (nom == "Erika") {
        std::cout << "Soigne 50 PV d'un Pokémon Plante.\n";
        joueur.soignerActif(50); // Simplifié: devrait vérifier le type
    }
    else if (nom == "Misty") {
        std::cout << "Attache des énergies Eau selon les piles.\n";
        // Nécessite un système de pile ou face
    }
    else if (nom == "Giovanni") {
        std::cout << "Les attaques infligent +10 dégâts ce tour.\n";
        // Nécessite un système de buffs temporaires
    }
    else if (nom == "Brock") {
        std::cout << "Attache une énergie Combat à Grolem ou Onix.\n";
        joueur.ajouterEnergieActif();
    }
    else if (nom == "Sabrina") {
        std::cout << "L'adversaire change son Pokémon actif.\n";
        // Nécessite l'accès à l'adversaire
    }
    else {
        std::cout << "(Effet non implémenté pour " << nom << ")\n";
    }
}
