#pragma once
#include "CarteBase.hpp"
#include <string>

class CartePokemon : public CarteBase {
private:
    std::string nom;
    std::string type;           // Type elementaire (Grass, Fire, Water, etc.)
    int pvMax;                  // PV maximum
    int pv;                     // PV actuels
    int degats;                 // Degats de l'attaque principale
    int energie;                // Energie attachee au Pokémon
    int coutAttaque;            // Cout en energie pour attaquer
    int coutRetraite;           // Cout en energie pour battre en retraite
    std::string faiblesse;      // Type de faiblesse

public:
    // Constructeur
    CartePokemon(const std::string& nom, const std::string& type, int pv, 
                 int degats, int coutAttaque, int coutRetraite,
                 const std::string& faiblesse = "");
    
    // Accesseur
    TypeCarte getType() const override;
    const std::string& getNom() const override;
    const std::string& getTypeElementaire() const;
    const std::string& getFaiblesse() const;
    
    int getPV() const;
    int getPVMax() const;
    int getEnergie() const;
    int getCoutRetraite() const;

    // Etat du pokemon
    bool estKO() const;
    bool peutAttaquer() const;
    bool peutRetraite() const;
    
    // Actions
    void attaquer(CartePokemon& cible);
    void ajouterEnergie(int qte = 1);
    void payerRetraite();
    void soigner(int montant);
    void recevoirDegats(int montant);

    void afficher() const;
};
