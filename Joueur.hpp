#pragma once

#include <string>
#include <vector>
#include "carte.hpp"

class Joueur {
private:
    std::string nom;
    std::vector<Carte> main;
    std::vector<Carte> pioche;
    std::vector<Carte> banc;
    Carte carteActive;
    int point; //Un par pokemon mis KO

public:
    // Constructeurs
    //Joueur(const std::string& nom);
    Joueur(const std::string& nom, std::vector<Carte> main, std::vector<Carte> pioche);

    // extracteurs
    std::string getNom() const;
    const Carte& getCarteActive() const;
    std::vector<Carte> getMain();
    std::vector<Carte> getPioche();
    std::vector<Carte> getBanc();
    int getPoint();
    
    // Gestion de la pioche
    void initialiserPioche(const std::vector<Carte>& cartes);
    void melangerPioche();
    bool piocheVide() const;
    void piocher(int nombre = 1);

    // Gestion des cartes
    void piocher(const Carte& carte);
    void jouerCarte(size_t index);

    // Combat
    bool gagne() const;
    void attaquer(Joueur& adversaire);
};
