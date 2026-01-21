#include "joueur.hpp"
#include <iostream>
#include <algorithm>
#include <random>

// ------------------
// CONSTRUCTEURS
// ------------------
Joueur::Joueur(const std::string& nom)
    : nom(nom), points(0), carteActive() {}

Joueur::Joueur(const std::string& nom,
               const std::vector<Carte>& main,
               const std::vector<Carte>& pioche)
    : nom(nom), points(0), pioche(pioche), main(main), banc(), carteActive() {
    melangerPioche();
}

// ------------------
// GETTERS
// ------------------
const std::string& Joueur::getNom() const {
    return nom;
}

int Joueur::getPoints() const {
    return points;
}

const Carte& Joueur::getCarteActive() const {
    return carteActive;
}

const std::vector<Carte>& Joueur::getMain() const {
    return main;
}

const std::vector<Carte>& Joueur::getPioche() const {
    return pioche;
}

const std::vector<Carte>& Joueur::getBanc() const {
    return banc;
}

// ------------------
// ÉTAT DU JOUEUR
// ------------------
bool Joueur::aCarteActive() const {
    return !carteActive.estK.O();
}

bool Joueur::bancVide() const {
    return banc.empty();
}

bool Joueur::piocheVide() const {
    return pioche.empty();
}

bool Joueur::aPerdu() const {
    return piocheVide() && !aCarteActive() && bancVide();
}

// ------------------
// PIOCHE
// ------------------
void Joueur::initialiserPioche(const std::vector<Carte>& cartes) {
    pioche = cartes;
    melangerPioche();
}

void Joueur::melangerPioche() {
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(pioche.begin(), pioche.end(), g);
}

void Joueur::piocher(int nombre) {
    for (int i = 0; i < nombre; ++i) {
        if (pioche.empty()) {
            std::cout << nom << " ne peut plus piocher (pioche vide)." << std::endl;
            return;
        }
        main.push_back(pioche.back());
        pioche.pop_back();
    }
}

// ------------------
// GESTION DES CARTES
// ------------------
void Joueur::jouerCarte(size_t index, bool versBanc) {
    if (index >= main.size()) {
        std::cout << "Index de carte invalide !" << std::endl;
        return;
    }

    if (!versBanc) { // carte active
        if (aCarteActive()) {
            std::cout << "Une carte active est déjà en jeu !" << std::endl;
            return;
        }
        carteActive = main[index];
        std::cout << nom << " joue " << carteActive.getNom()
                  << " comme carte active." << std::endl;
    } else { // banc
        if (banc.size() >= 3) {
            std::cout << "Banc plein (max 3 cartes)." << std::endl;
            return;
        }
        banc.push_back(main[index]);
        std::cout << nom << " joue " << main[index].getNom()
                  << " sur le banc." << std::endl;
    }

    main.erase(main.begin() + index);
}

void Joueur::promouvoirDepuisBanc(size_t index) {
    if (index >= banc.size()) {
        std::cout << "Index de banc invalide !" << std::endl;
        return;
    }

    if (aCarteActive()) {
        std::cout << "Une carte active est déjà en jeu !" << std::endl;
        return;
    }

    carteActive = banc[index];
    banc.erase(banc.begin() + index);

    std::cout << nom << " promeut " << carteActive.getNom()
              << " comme carte active." << std::endl;
}

void Joueur::mortCarte() {
    if (carteActive.estK.O()) {
        std::cout << nom << " perd sa carte active (KO)." << std::endl;
        carteActive = Carte(); // carte vide
    }
}

// ------------------
// COMBAT
// ------------------
bool Joueur::peutAttaquer() const {
    return aCarteActive();
}

void Joueur::attaquer(Joueur& adversaire) {
    if (!peutAttaquer()) {
        std::cout << nom << " ne peut pas attaquer (pas de carte active)." << std::endl;
        return;
    }

    if (!adversaire.aCarteActive()) {
        std::cout << adversaire.getNom()
                  << " n'a pas de carte active." << std::endl;
        return;
    }

    std::cout << nom << " attaque " << adversaire.getNom() << " !" << std::endl;

    adversaire.carteActive.subirDegats(carteActive.getDegatsAttaque());

    if (adversaire.carteActive.estK.O()) {
        std::cout << adversaire.getNom()
                  << " voit sa carte active mise KO !" << std::endl;

        points++;
        adversaire.mortCarte();
    }
}
