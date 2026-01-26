#include "joueur.hpp"
#include <iostream>
#include <algorithm>
#include <random>

// ------------------
// CONSTRUCTEURS
// ------------------
Joueur::Joueur(const std::string& nom)
    : nom(nom), points(0), carteActive() {}

Joueur::Joueur(const std::string& nom,
               const std::vector<Carte>& main,
               const std::vector<Carte>& pioche)
    : nom(nom), points(0), pioche(pioche), main(main), banc(), carteActive(), supporterDejaJoue(false) {
    melangerPioche();
}

// ------------------
// EXTRACTEURS 
// ------------------
const std::string& Joueur::getNom() const {
    return nom;
}

int Joueur::getPoints() const {
    return points;
}

const Carte& Joueur::getCarteActive() const {
    return carteActive;
}

const std::vector<Carte>& Joueur::getMain() const {
    return main;
}

const std::vector<Carte>& Joueur::getPioche() const {
    return pioche;
}

const std::vector<Carte>& Joueur::getBanc() const {
    return banc;
}

bool Joueur::getSupporterDejaJoue() const {
    return supporterDejaJoue;
}

bool Joueur::getEnergieDejaAttachee() const {
    return energieDejaAttachee;
}


// ------------------
// ÉTAT DU JOUEUR
// ------------------
bool Joueur::aCarteActive() const {
    return !carteActive.estKO();
}

bool Joueur::bancVide() const {
    return banc.empty();
}

bool Joueur::piocheVide() const {
    return pioche.empty();
}

bool Joueur::aPerdu() const {
    return !aCarteActive() && bancVide();
}
// ------------------
// TOUR
// ------------------
void Joueur::debutTour() {
    if (main.size()<10){ //On a maximum 10 cartes dans la main
        piocher(1);
    }
}

void Joueur::finTour() {
    // réservé pour plus tard (statuts, effets, etc.)
}



// ------------------
// PIOCHE
// ------------------
void Joueur::initialiserPioche(const std::vector<Carte>& cartes) {
    pioche = cartes;
    melangerPioche();
}

void Joueur::melangerPioche() {
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(pioche.begin(), pioche.end(), g);
}

void Joueur::piocher(int nombre) {
    if (main.size() + nombre >= 10){
            std::cout << nom << " ne peut plus piocher (main pleine)." << std::endl;
            return;
        }
    for (int i = 0; i < nombre; ++i) {
        if (pioche.empty()) {
            std::cout << nom << " ne peut plus piocher (pioche vide)." << std::endl;
            return;
        }
        main.push_back(pioche.back());
        pioche.pop_back();
    }
}

// ------------------
// GESTION DES CARTES
// ------------------
void Joueur::jouerCarte(size_t index, bool versBanc) {
    if (index >= main.size()) {
        std::cout << "Index de carte invalide !" << std::endl;
        return;
    }

    if (!versBanc) { // carte active
        if (aCarteActive()) {
            std::cout << "Une carte active est déjà en jeu !" << std::endl;
            return;
        }
        carteActive = main[index];
        std::cout << nom << " joue " << carteActive.getNom()
                  << " comme carte active." << std::endl;
    } else { // banc
        if (banc.size() >= 3) {
            std::cout << "Banc plein (max 3 cartes)." << std::endl;
            return;
        }
        banc.push_back(main[index]);
        std::cout << nom << " joue " << main[index].getNom()
                  << " sur le banc." << std::endl;
    }

    main.erase(main.begin() + index);
}

void Joueur::promouvoirDepuisBanc(size_t index) {
    if (index >= banc.size()) {
        std::cout << "Index de banc invalide !" << std::endl;
        return;
    }

    if (aCarteActive()) {
        std::cout << "Une carte active est déjà en jeu !" << std::endl;
        return;
    }

    carteActive = banc[index];
    banc.erase(banc.begin() + index);

    std::cout << nom << " promeut " << carteActive.getNom()
              << " comme carte active." << std::endl;
}

void Joueur::mortCarte() {
    if (carteActive.estKO()) {
        std::cout << nom << " perd sa carte active (KO)." << std::endl;
        carteActive = Carte(); // carte vide
    }
}
// ------------------
// ENERGIE
// ------------------
bool Joueur::peutAttacherEnergie() const {
    return (aCarteActive() || !banc.empty()) && !energieDejaAttachee();
}

void Joueur::attacherEnergieACarteActive(int quantite) {
    if (!aCarteActive()) {
        std::cout << nom << " n'a pas de carte active." << std::endl;
        return;
    }
    carteActive.ajouterEnergie(quantite);

    std::cout << nom << " attache " << quantite
              << " énergie(s) à " << carteActive.getNom() << "."
              << std::endl;
}

void Joueur::attacherEnergieAuBanc(size_t indexBanc, int quantite) {
    if (indexBanc >= banc.size()) {
        std::cout << "Index de banc invalide." << std::endl;
        return;
    }

    banc[indexBanc].ajouterEnergie(quantite);

    std::cout << nom << " attache " << quantite
              << " énergie(s) à " << banc[indexBanc].getNom()
              << " sur le banc." << std::endl;
}

void Joueur::marquerSupporterJoue() {
    energieDejaAttachee = true;
}

void Joueur::resetSupporterTour() { // A chaque debut de tour
    energieDejaAttachee = false;
}



// ------------------
// COMBAT
// ------------------
bool Joueur::peutAttaquer() const {
    return aCarteActive() && carteActive.peutAttaquer();
}

void Joueur::attaquer(Joueur& adversaire) {
    if (!peutAttaquer()) {
        std::cout << nom << " ne peut pas attaquer (pas de carte active)." << std::endl;
        return;
    }

    if (!adversaire.aCarteActive()) {
        std::cout << adversaire.getNom()
                  << " n'a pas de carte active." << std::endl;
        return;
    }

    std::cout << nom << " attaque " << adversaire.getNom() << " !" << std::endl;

    adversaire.carteActive.subirDegats(carteActive.getDegatsAttaque());

    if (adversaire.carteActive.estKO()) {
        std::cout << adversaire.getNom()
                  << " voit sa carte active mise KO !" << std::endl;

        points++;
        adversaire.mortCarte();
    }
}

//-------------------
//RETRAITE
//-------------------
bool Joueur::peutBattreEnRetraite() const {
    return aCarteActive()
        && !banc.empty()
        && carteActive.peutBattreEnRetraite();
}

void Joueur::battreEnRetraite(size_t indexBanc) {
    if (!peutBattreEnRetraite()) {
        std::cout << nom << " ne peut pas battre en retraite." << std::endl;
        return;
    }

    if (indexBanc >= banc.size()) {
        std::cout << "Index de banc invalide." << std::endl;
        return;
    }

    // La carte active paie son coût de retraite
    carteActive.battreEnRetraite();

    // Échange active ↔ banc
    Carte ancienneActive = carteActive;
    carteActive = banc[indexBanc];
    banc[indexBanc] = ancienneActive;

    std::cout << nom << " bat en retraite et envoie "
              << carteActive.getNom()
              << " au combat." << std::endl;
}

void Joueur::promouvoirApresKO(size_t indexBanc) {
    if (!banc.empty() && !aCarteActive()) {
        if (indexBanc >= banc.size()) {
            std::cout << "Index de banc invalide." << std::endl;
            return;
        }

        carteActive = banc[indexBanc];
        banc.erase(banc.begin() + indexBanc);

        std::cout << nom << " promeut "
                  << carteActive.getNom()
                  << " après un KO." << std::endl;
    }
}





void Joueur::afficherEtat() const {
    std::cout << "\n--- " << nom << " ---\n";
    std::cout << "Points : " << points << std::endl;

    if (aCarteActive()) {
        std::cout << "Carte active : "
                  << carteActive.getNom()
                  << " (PV: " << carteActive.getPointsDeVie()
                  << ", Énergie: " << carteActive.getEnergieAttachee()
                  << ")\n";
    } else {
        std::cout << "Carte active : Aucune\n";
    }

    std::cout << "Banc (" << banc.size() << "/3) :\n";
    for (size_t i = 0; i < banc.size(); ++i) {
        std::cout << "  [" << i << "] "
                  << banc[i].getNom()
                  << " (PV: " << banc[i].getPointsDeVie()
                  << ", Énergie: " << banc[i].getEnergieAttachee()
                  << ")\n";
    }

    std::cout << "Main : " << main.size() << " carte(s)\n";
    std::cout << "Pioche : " << pioche.size() << " carte(s)\n";
}

// ------------------
// SUPPORTER
// ------------------

// Supporter
bool Joueur::aDejaJoueSupporterCeTour() const {
    return supporterDejaJoue;
}

void Joueur::marquerSupporterJoue() {
    supporterDejaJoue = true;
}

void Joueur::resetSupporterTour() { // A chaque debut de tour
    supporterDejaJoue = false;
}







