#pragma once

#include <string>
#include <vector>
#include "carte.hpp"

class Joueur {
private:
    std::string nom;
    int points;

    std::vector<Carte> pioche;
    std::vector<Carte> main;
    std::vector<Carte> banc;

    Carte carteActive; // Carte active (vide si aucune)

public:
    // Constructeurs
    Joueur(const std::string& nom);
    Joueur(const std::string& nom,
           const std::vector<Carte>& main,
           const std::vector<Carte>& pioche);

    // Getters (PAS de copies inutiles)
    const std::string& getNom() const;
    int getPoints() const;

    const Carte& getCarteActive() const;
    const std::vector<Carte>& getMain() const;
    const std::vector<Carte>& getPioche() const;
    const std::vector<Carte>& getBanc() const;

    // ----- État du joueur -----
    bool aCarteActive() const;
    bool bancVide() const;
    bool piocheVide() const;
    bool aPerdu() const;

    // ----- Gestion de la pioche -----
    void initialiserPioche(const std::vector<Carte>& cartes);
    void melangerPioche();
    void piocher(int nombre = 1);

    // ----- Gestion des cartes -----
    void jouerCarte(size_t index, bool versBanc); // false = active, true = banc
    void promouvoirDepuisBanc(size_t index);
    void mortCarte(); // retire la carte active si KO

    // ----- Combat -----
    bool peutAttaquer() const;
    void attaquer(Joueur& adversaire);
};
