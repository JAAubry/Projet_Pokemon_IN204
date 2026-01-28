#pragma once
#include "CarteBase.hpp"
#include <string>

class CartePokemon : public CarteBase {
private:
    std::string nom;
    std::string type;           // Type élémentaire (Grass, Fire, Water, etc.)
    int pvMax;                  // PV maximum
    int pv;                     // PV actuels
    int degats;                 // Dégâts de l'attaque principale
    int energie;                // Énergie attachée au Pokémon
    int coutAttaque;            // Coût en énergie pour attaquer
    int coutRetraite;           // Coût en énergie pour battre en retraite
    std::string faiblesse;      // Type de faiblesse

public:
    CartePokemon(const std::string& nom, const std::string& type, int pv, 
                 int degats, int coutAttaque, int coutRetraite,
                 const std::string& faiblesse = "");

    TypeCarte getType() const override;
    const std::string& getNom() const override;
    const std::string& getTypeElementaire() const;
    const std::string& getFaiblesse() const;
    
    int getPV() const;
    int getPVMax() const;
    int getEnergie() const;
    int getCoutRetraite() const;

    bool estKO() const;
    bool peutAttaquer() const;
    bool peutRetraite() const;

    void attaquer(CartePokemon& cible);
    void ajouterEnergie(int qte = 1);
    void payerRetraite();
    void soigner(int montant);
    void recevoirDegats(int montant);

    void afficher() const;
};
