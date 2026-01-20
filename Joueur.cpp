#include "joueur.hpp"
#include <iostream>
#include <algorithm>   // std::shuffle
#include <random>

// Constructeur
Joueur::Joueur(const std::string& nom) : nom(nom), carteActive() {}
Joueur(const std::string& nom, std::vector<Carte> main, std::vector<Carte> pioche): nom(nom), main(main), pioche(pioche),
                                                    banc(), point(0), carteActive() {}


// Extraxteurs
std::string Joueur::getNom() const {
    return nom;
}

const Carte& Joueur::getCarteActive() const {
    return carteActive;
}
std::vector<Carte> Joueur::getMain() const{
    return main;
}
std::vector<Carte> Joueur::getPioche() const{
    return pioche;
}
std::vector<Carte> Joueur::getBanc() const{
    return banc;
}
int Joueur::getPoint(){
    return point;
}

// Gestion des cartes
void Joueur::piocher(const Carte& carte) {
    main.push_back(carte);
}

void Joueur::jouerCarte(size_t index) {
    if (index < main.size()) {
        carteActive = main[index];
        main.erase(main.begin() + index);
    } else {
        std::cout << "Index de carte invalide !" << std::endl;
    }
}

// Combat
void Joueur::attaquer(Joueur& adversaire) {
    std::cout << nom << " attaque " << adversaire.getNom() << " !" << std::endl;
    adversaire.carteActive.subirDegats(carteActive.getDegatsAttaque());
}
