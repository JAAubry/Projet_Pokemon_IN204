#pragma once
#include <string>

class Joueur;

enum class TypeCarte {
    Pokemon,
    Dresseur
};

class CarteBase {
public:
    virtual ~CarteBase() = default;

    virtual TypeCarte getType() const = 0;
    virtual const std::string& getNom() const = 0;

    // Par défaut : aucune action (utilisé par Dresseur)
    virtual void appliquerEffet(Joueur&) {}
};
