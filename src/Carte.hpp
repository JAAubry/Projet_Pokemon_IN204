#pragma once
#include <string>

class Carte {
private:
    std::string nom;
    int pointsDeVie;
    int pointsDeVieMax;
    int degatsAttaque;
    int energieRetraite;
    int energieAttaque;
    int energieAttachee;


public:
    // Constructeurs
    Carte(); //carte 'vide'
    Carte(const std::string& nom, int pv, int pvmax, int degats,int energieR, int energieA);

    // extracteur
    const std::string& getNom() const;
    int getPointsDeVie() const;
    int getPointsDeVieMax() const;
    int getDegatsAttaque() const;
    int getEnergieRetraite() const;
    int getEnergieAttaque() const;
    int getEnergieAttachee() const;

    // Combat
    void subirDegats(int degats);
    // Etat de la carte 
    bool estKO() const;
    bool estValide() const;
    // Gestion de l'energie
    void ajouterEnergie(int quantite = 1);
    bool peutAttaquer() const;
    bool peutBattreEnRetraite() const;
    void battreEnRetraite();

    void soigner(int pv);

};
