#include "Joueur.hpp"
#include "CarteDresseur.hpp"
#include <random>
#include <iostream>
#include <algorithm>

// ------------------
// CONSTRUCTEUR
// ------------------
Joueur::Joueur(const std::string& nom)
    : nom(nom),
      supporterJoue(false),
      energieJouee(false) {}

// ------------------
// GETTERS CORRIGÉS
// ------------------
const std::string& Joueur::getNom() const {
    return nom;
}

const std::vector<std::unique_ptr<CarteBase>>& Joueur::getMain() const {
    return main;
}

const std::vector<std::unique_ptr<CartePokemon>>& Joueur::getBanc() const {
    return banc;
}

// CORRIGÉ: retourne une référence au lieu d'une copie
const std::unique_ptr<CartePokemon>& Joueur::getCarteActive() const {
    return actif;
}

CartePokemon* Joueur::getPokemonActif() {
    return actif.get();
}

const CartePokemon* Joueur::getPokemonActif() const {
    return actif.get();
}

// ------------------
// ÉTAT
// ------------------
bool Joueur::aPokemonActif() const {
    return actif != nullptr && !actif->estKO();
}

bool Joueur::peutPlacerPokemonActif() const {
    // Vérifie s'il y a des Pokémon sur le banc ou dans la main
    if (!banc.empty()) return true;
    
    for (const auto& carte : main) {
        if (carte->getType() == TypeCarte::Pokemon) {
            return true;
        }
    }
    return false;
}

bool Joueur::peutContinuer() const {
    // Un joueur peut continuer s'il a un Pokémon actif OU s'il peut en placer un
    return aPokemonActif() || peutPlacerPokemonActif();
}

bool Joueur::aPerdu() const {
    // AMÉLIORATION: Un joueur perd s'il:
    // 1. Ne peut pas piocher au début de son tour (deck vide)
    // 2. N'a plus de Pokémon actif ET ne peut pas en placer un
    
    if (pioche.empty() && !aPokemonActif() && !peutPlacerPokemonActif()) {
        return true;
    }
    
    if (!aPokemonActif() && !peutPlacerPokemonActif()) {
        return true;
    }
    
    return false;
}

// ------------------
// INITIALISATION
// ------------------
void Joueur::setDeck(std::vector<std::unique_ptr<CarteBase>> deck) {
    pioche = std::move(deck);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pioche.begin(), pioche.end(), g);
    piocher(7);  // Pioche initiale de 7 cartes (règle standard)
}

// ------------------
// PIOCHE
// ------------------
void Joueur::piocher(int n) {
    for (int i = 0; i < n && !pioche.empty(); ++i) {
        main.push_back(std::move(pioche.back()));
        pioche.pop_back();
        std::cout << nom << " pioche une carte.\n";
    }
    
    if (pioche.empty()) {
        std::cout << nom << " n'a plus de cartes dans son deck!\n";
    }
}

// ------------------
// JOUER UNE CARTE
// ------------------
void Joueur::jouerCarte(std::size_t index) {
    if (index >= main.size()) {
        std::cout << "Index invalide!\n";
        return;
    }

    if (main[index]->getType() == TypeCarte::Pokemon) {
        auto pokemon = std::unique_ptr<CartePokemon>(
            static_cast<CartePokemon*>(main[index].release())
        );

        if (!actif) {
            actif = std::move(pokemon);
            std::cout << actif->getNom() << " devient le Pokémon actif.\n";
        } else if (banc.size() < 5) {  // Limite standard à 5 Pokémon sur le banc
            std::cout << pokemon->getNom() << " est placé sur le banc.\n";
            banc.push_back(std::move(pokemon));
        } else {
            std::cout << "Le banc est plein (5 Pokémon maximum)!\n";
            return;  // Ne pas supprimer la carte de la main si on ne peut pas la jouer
        }
    } else {
        // Carte Dresseur
        auto* dresseur = static_cast<CarteDresseur*>(main[index].get());
        
        if (dresseur->getSousType() == TypeDresseur::Supporter) {
            if (supporterJoue) {
                std::cout << "Vous avez déjà joué un Supporter ce tour!\n";
                return;
            }
            supporterJoue = true;
        }
        
        main[index]->appliquerEffet(*this);
    }

    main.erase(main.begin() + index);
}

// ------------------
// COMBAT
// ------------------
void Joueur::attaquer(Joueur& adversaire) {
    if (!actif) {
        std::cout << "Vous n'avez pas de Pokémon actif!\n";
        return;
    }
    
    if (!adversaire.actif) {
        std::cout << "L'adversaire n'a pas de Pokémon actif!\n";
        return;
    }
    
    if (!actif->peutAttaquer()) {
        std::cout << actif->getNom() << " n'a pas assez d'énergie pour attaquer!\n";
        return;
    }

    actif->attaquer(*adversaire.actif);

    // Si le Pokémon adverse est K.O., il doit être retiré
    if (adversaire.actif->estKO()) {
        std::cout << adversaire.actif->getNom() << " de " 
                  << adversaire.nom << " est mis K.O.!\n";
        adversaire.actif.reset();
        
        // L'adversaire doit placer un nouveau Pokémon actif s'il en a
        if (!adversaire.banc.empty()) {
            std::cout << adversaire.nom << " doit choisir un nouveau Pokémon actif du banc.\n";
        }
    }
}

// ------------------
// RETRAITE (NOUVELLE FONCTIONNALITÉ)
// ------------------
void Joueur::batterEnRetraite(std::size_t indexBanc) {
    if (!actif) {
        std::cout << "Vous n'avez pas de Pokémon actif!\n";
        return;
    }
    
    if (indexBanc >= banc.size()) {
        std::cout << "Index de banc invalide!\n";
        return;
    }
    
    if (!actif->peutRetraite()) {
        std::cout << actif->getNom() 
                  << " n'a pas assez d'énergie pour battre en retraite! (Coût: " 
                  << actif->getCoutRetraite() << ", Disponible: " 
                  << actif->getEnergie() << ")\n";
        return;
    }
    
    // Payer le coût de retraite
    actif->payerRetraite();
    
    // Échanger le Pokémon actif avec celui du banc
    std::cout << actif->getNom() << " bat en retraite et " 
              << banc[indexBanc]->getNom() << " devient actif.\n";
    
    std::swap(actif, banc[indexBanc]);
}

// ------------------
// EFFETS (pour cartes Dresseur)
// ------------------
void Joueur::soignerActif(int montant) {
    if (!actif) {
        std::cout << "Vous n'avez pas de Pokémon actif à soigner!\n";
        return;
    }
    
    actif->soigner(montant);
}

void Joueur::ajouterEnergieActif() {
    if (!actif) {
        std::cout << "Vous n'avez pas de Pokémon actif!\n";
        return;
    }
    
    if (energieJouee) {
        std::cout << "Vous avez déjà attaché une énergie ce tour!\n";
        return;
    }
    
    actif->ajouterEnergie(1);
    energieJouee = true;
}

void Joueur::voirTopDeck(int n) {
    int cartes = std::min(n, static_cast<int>(pioche.size()));
    std::cout << "Top " << cartes << " carte(s) du deck:\n";
    
    for (int i = pioche.size() - 1; i >= std::max(0, static_cast<int>(pioche.size()) - cartes); --i) {
        std::cout << " - " << pioche[i]->getNom() << "\n";
    }
}

// ------------------
// TOUR DE JEU
// ------------------
void Joueur::debutTour() {
    supporterJoue = false;
    energieJouee = false;
    
    // Vérifier si on peut piocher
    if (!pioche.empty()) {
        piocher(1);
    } else {
        std::cout << nom << " ne peut pas piocher (deck vide)!\n";
    }
    
    // Si pas de Pokémon actif et qu'on en a sur le banc, on doit en placer un
    if (!aPokemonActif() && !banc.empty()) {
        std::cout << nom << " doit placer un Pokémon du banc en position active!\n";
    }
}

void Joueur::finTour() {
    // Placeholder pour d'éventuels effets de fin de tour
}

void Joueur::jouerTour(Joueur& adversaire) {
    debutTour();
    afficher();
}

// ------------------
// AFFICHAGE
// ------------------
void Joueur::afficher() const {
    std::cout << "Joueur: " << nom << "\n";


    std::cout << "\nPokémon Actif:\n";
    if (actif) {
        std::cout << "  ";
        actif->afficher();
    } else {
        std::cout << "  (Aucun)\n";
    }

    std::cout << "\nBanc (" << banc.size() << "/5):\n";
    if (banc.empty()) {
        std::cout << "  (Vide)\n";
    } else {
        for (size_t i = 0; i < banc.size(); ++i) {
            std::cout << "  [" << i << "] ";
            banc[i]->afficher();
        }
    }

    std::cout << "Main: " << main.size() << " carte(s)"
              << "Pioche: " << pioche.size() << " carte(s)\n";
}

void Joueur::afficherMainDetaille() const {
    std::cout << "\nMain détaillée:\n";
    if (main.empty()) {
        std::cout << "  (Main vide)\n";
    } else {
        for (std::size_t i = 0; i < main.size(); ++i) {
            std::string typeStr = (main[i]->getType() == TypeCarte::Pokemon) ? "Pokémon" : "Dresseur";
            std::cout << "  [" << i << "] " << typeStr << " - " << main[i]->getNom() << "\n";
        }
    }
}
