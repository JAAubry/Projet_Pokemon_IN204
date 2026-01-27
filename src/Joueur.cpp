#include "Joueur.hpp"
#include <iostream>
#include <algorithm>
#include <random>

Joueur::Joueur(const std::string& nom)
    : nom(nom), points(0), supporterDejaJoue(false) {}

void Joueur::initialiserDeck(std::vector<std::unique_ptr<CarteBase>> deck) {
    pioche = std::move(deck);
    std::shuffle(pioche.begin(), pioche.end(),
                 std::mt19937{std::random_device{}()});
    piocher(5);
}

void Joueur::debutTour() {
    supporterDejaJoue = false;
    piocher(1);
}

void Joueur::piocher(int n) {
    while (n-- && !pioche.empty()) {
        main.push_back(std::move(pioche.back()));
        pioche.pop_back();
    }
}

void Joueur::jouerCarteDepuisMain(size_t index) {
    if (index >= main.size()) return;

    if (auto* p = dynamic_cast<CartePokemon*>(main[index].get())) {
        if (!carteActive) {
            carteActive.reset(static_cast<CartePokemon*>(main[index].release()));
        } else if (banc.size() < 3) {
            banc.push_back(std::unique_ptr<CartePokemon>(
                static_cast<CartePokemon*>(main[index].release())));
        } else return;

        main.erase(main.begin() + index);
        return;
    }

    if (auto* d = dynamic_cast<CarteDresseur*>(main[index].get())) {
        if (d->getTypeDresseur() == TypeDresseur::Supporter && supporterDejaJoue)
            return;

        d->appliquerEffet(*this);
        defausse.push_back(std::move(main[index]));
        main.erase(main.begin() + index);
    }
}

void Joueur::attaquer(Joueur& adversaire) {
    if (!carteActive || !adversaire.carteActive) return;

    carteActive->attaquer(*adversaire.carteActive);

    if (adversaire.carteActive->estKO()) {
        adversaire.mortCarteActive();
        points++;
    }
}

void Joueur::mortCarteActive() {
    defausse.push_back(std::move(carteActive));
    if (!banc.empty()) promouvoirApresKO(0);
}

void Joueur::promouvoirApresKO(size_t index) {
    carteActive = std::move(banc[index]);
    banc.erase(banc.begin() + index);
}

void Joueur::attacherEnergieActive(int q) {
    if (carteActive) carteActive->ajouterEnergie(q);
}

bool Joueur::aPerdu() const {
    return !carteActive && banc.empty() && pioche.empty();
}

bool Joueur::aCarteActive() const {
    return carteActive != nullptr;
}

void Joueur::soignerCarteActive(int pv) {
    if (carteActive) carteActive->subirDegats(-pv);
}

void Joueur::afficherEtat() const {
    std::cout << "\n--- " << nom << " ---\n";
    if (carteActive) carteActive->afficher();
    else std::cout << "Aucune carte active\n";
    std::cout << "Main: " << main.size()
              << " | Banc: " << banc.size()
              << " | Pioche: " << pioche.size()
              << std::endl;
}

void Joueur::marquerSupporterJoue() {
    supporterDejaJoue = true;
}

bool Joueur::aDejaJoueSupporterCeTour() const {
    return supporterDejaJoue;
}

const std::string& Joueur::getNom() const {
    return nom;
}
