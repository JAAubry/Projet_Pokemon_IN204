#pragma once
#include <string>

class Carte {
private:
    std::string nom;
    int pointsDeVie;
    int degatsAttaque;
    int energieRetraite;
    int energieAttaque;

public:
    // Constructeurs
    Carte(); //carte 'vide'
    Carte(const std::string& nom, int pv, int degats,int energieR, int energieA);

    // extracteur
    const std::string getNom() const;
    int getPointsDeVie() const;
    int getDegatsAttaque() const;
    int getEnergieRetraite() const;
    int getEnergieAttaque() const;

    // Combat
    void subirDegats(int degats);
    // Etat de la carte 
    bool estKO() const;
    bool estValide() const;
};
