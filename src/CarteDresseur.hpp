#pragma once

#include "CarteBase.hpp"
#include <string>

class Joueur;

enum class TypeDresseur {
    Objet,
    Supporter
};

class CarteDresseur : public CarteBase {
private:
    std::string nom;
    std::string effet;
    TypeDresseur type;

public:
    CarteDresseur(const std::string& nom,
                  const std::string& effet,
                  TypeDresseur type);

    // CarteBase
    TypeCarte getType() const override;
    const std::string& getNom() const override;

    // Dresseur
    TypeDresseur getTypeDresseur() const;
    void appliquerEffet(Joueur& joueur) override;
};
