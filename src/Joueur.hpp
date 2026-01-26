#pragma once

#include <string>
#include <vector>
#include "carte.hpp"

class Joueur {
private:
    std::string nom;
    int points;

    std::vector<Carte> pioche;
    std::vector<Carte> main;
    std::vector<Carte> banc;

    Carte carteActive; // Carte active (vide si aucune)
    bool supporterDejaJoue; // Un supporter par tour
    bool energieDejaAttachee;


public:
    // Constructeurs
    Joueur(const std::string& nom);
    Joueur(const std::string& nom,
           const std::vector<Carte>& main,
           const std::vector<Carte>& pioche);

    // Extracteurs
    const std::string& getNom() const;
    int getPoints() const;

    const Carte& getCarteActive() const;
    const std::vector<Carte>& getMain() const;
    const std::vector<Carte>& getPioche() const;
    const std::vector<Carte>& getBanc() const;
    bool getSupporterDejaJoue() const;
    bool getEnergieDejaAttachee() const;

    // ----- État du joueur -----
    bool aCarteActive() const;
    bool bancVide() const;
    bool piocheVide() const;
    bool aPerdu() const;

    // ----- Tour de jeu -----
    void debutTour();
    void finTour();

    // ----- Gestion de la pioche -----
    void initialiserPioche(const std::vector<Carte>& cartes);
    void melangerPioche();
    void piocher(int nombre = 1);

    // ----- Gestion des cartes -----
    void jouerCarte(size_t index, bool versBanc); // false = active, true = banc
    void promouvoirDepuisBanc(size_t index);
    void mortCarte(); // retire la carte active si KO

    // ----- Combat -----
    bool peutAttaquer() const;
    void attaquer(Joueur& adversaire);

    // ----- Énergie -----
    bool peutAttacherEnergie() const;
    void attacherEnergieACarteActive(int quantite = 1);
    void attacherEnergieAuBanc(size_t indexBanc, int quantite = 1);
    
    bool aDejaAttacheEnergieCeTour() const;
    void marquerEnergieAttachee();
    void resetEnergieTour();



    // ----- Retraite --------
    // Retraite
    bool peutBattreEnRetraite() const;
    void battreEnRetraite(size_t indexBanc);
    void promouvoirApresKO(size_t indexBanc);
    
        
    // ----- Affichage -----
    void afficherEtat() const;

    // ----- Supporters -----
    bool aDejaJoueSupporterCeTour() const;
    void marquerSupporterJoue();
    void resetSupporterTour();

    // ----- Effets Dresseur -----
    void soignerCarteActive(int pv);

};
 