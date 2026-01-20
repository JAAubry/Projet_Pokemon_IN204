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
    Carte();
    Carte(const std::string& nom, int pv, int degats,int energieR, int energieA);

    // extracteur
    std::string getNom() const;
    int getPointsDeVie() const;
    int getDegatsAttaque() const;
    int getEnergieRetraite() const;
    int getEnergieAttaque() const;

    // Méthodes
    void subirDegats(int degats);
    bool estKO() const;
};

#endif // CARTE_HPP
