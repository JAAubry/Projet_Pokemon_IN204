#pragma once
#include <string>

class Joueur; // forward declaration

enum class TypeDresseur {
    Supporter,
    Objet
};

class Dresseur {
private:
    std::string nom;
    std::string description;
    TypeDresseur type;

public:
    Dresseur();
    Dresseur(const std::string& nom, const std::string& description, TypeDresseur type);
    // Extracteur
    const std::string& getNom() const;
    TypeDresseur getType() const;
    const std::string& getDescription() const;

    // Effet de la carte
    void appliquerEffet(Joueur& joueur) const;
    //Verification
    bool peutEtreJoue(const Joueur& joueur) const;

};
