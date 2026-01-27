#pragma once

#include <string>
#include <vector>
#include <memory>

#include "CarteBase.hpp"
#include "CartePokemon.hpp"
#include "CarteDresseur.hpp"

class Joueur {
private:
    std::string nom;
    int points;

    std::vector<std::unique_ptr<CarteBase>> pioche;
    std::vector<std::unique_ptr<CarteBase>> main;
    std::vector<std::unique_ptr<CarteBase>> defausse;

    std::unique_ptr<CartePokemon> carteActive;
    std::vector<std::unique_ptr<CartePokemon>> banc;

    bool supporterDejaJoue;

public:
    explicit Joueur(const std::string& nom);

    // Deck
    void initialiserDeck(std::vector<std::unique_ptr<CarteBase>> deck);

    // Tour
    void debutTour();
    void jouerTour(Joueur& adversaire);

    // Actions
    void jouerCarteDepuisMain(size_t index);
    void attaquer(Joueur& adversaire);
    void mortCarteActive();
    void promouvoirApresKO(size_t indexBanc);

    // Energie
    void attacherEnergieActive(int q = 1);

    // Etat
    bool aPerdu() const;
    bool aCarteActive() const;

    // Supporter
    void marquerSupporterJoue();
    bool aDejaJoueSupporterCeTour() const;

    // Utilitaires
    void piocher(int n = 1);
    void soignerCarteActive(int pv);
    void afficherEtat() const;

    const std::string& getNom() const;
};
