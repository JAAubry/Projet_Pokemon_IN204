#pragma once

#include "CarteBase.hpp"
#include <string>

class CartePokemon : public CarteBase {
private:
    std::string nom;
    int pointsDeVie;
    int degats;
    int energieAttachee;
    int coutAttaque;
    int coutRetraite;

public:
    CartePokemon(const std::string& nom,
                 int pv,
                 int degats,
                 int retraite,
                 int coutAttaque);

    // CarteBase
    TypeCarte getType() const override;
    const std::string& getNom() const override;

    // Combat
    bool estKO() const;
    bool peutAttaquer() const;
    void attaquer(CartePokemon& cible);
    void subirDegats(int degats);

    // Energie
    void ajouterEnergie(int n = 1);
    bool peutBattreEnRetraite() const;
    void battreEnRetraite();

    // Affichage
    void afficher() const;
};
