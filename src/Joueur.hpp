#pragma once

#include <string>
#include <vector>
#include <memory>

#include "CarteBase.hpp"
#include "CartePokemon.hpp"

class Joueur {
private:
    static constexpr std::size_t TAILLE_MAX_MAIN = 10;
    static constexpr std::size_t TAILLE_BANC = 3;
    static constexpr std::size_t NOMBRE_CARTES_DEBUT = 5;


    std::string nom;
    std::vector<std::unique_ptr<CarteBase>> pioche;
    std::vector<std::unique_ptr<CarteBase>> main;
    std::vector<std::unique_ptr<CartePokemon>> banc;

    std::unique_ptr<CartePokemon> actif;

    bool supporterJoue;
    bool energieJouee;

    bool peutPlacerPokemonActif() const;

public:
    explicit Joueur(const std::string& nom);

    // Accesseurs
    const std::string& getNom() const;
    const std::vector<std::unique_ptr<CarteBase>>& getMain() const;
    const std::vector<std::unique_ptr<CartePokemon>>& getBanc() const;
    const std::unique_ptr<CartePokemon>& getCarteActive() const;
    CartePokemon* getPokemonActif();  // Version non-const pour modifications
    const CartePokemon* getPokemonActif() const;  // Version const

    void setDeck(std::vector<std::unique_ptr<CarteBase>> deck);

    // ETAT DU JOUEUR
    bool aPerdu() const;
    bool aPokemonActif() const;
    bool peutContinuer() const;  

    // TOUR DE JEU
    void jouerTour(Joueur& adversaire);
    void debutTour();
    void finTour();

    // ACTIONS
    void piocher(int n = 1);
    void jouerCarte(std::size_t index);
    void attaquer(Joueur& adversaire);
    void batterEnRetraite(std::size_t indexBanc); 

    // EFFETS (pour les cartes Dresseur)
    void soignerActif(int pv);
    void ajouterEnergieActif();
    void voirTopDeck(int n);

    // AFFICHAGE
    void afficher() const;
    void afficherMainDetaille() const;
};
