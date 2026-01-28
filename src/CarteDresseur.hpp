#pragma once
#include "CarteBase.hpp"
#include <string>

enum class TypeDresseur {
    Objet,
    Supporter
};

class CarteDresseur : public CarteBase {
private:
    std::string nom;
    TypeDresseur type;

public:
    CarteDresseur(const std::string& nom, TypeDresseur type);

    TypeCarte getType() const override;
    const std::string& getNom() const override;

    TypeDresseur getSousType() const;

    void appliquerEffet(Joueur& joueur) override;
};
