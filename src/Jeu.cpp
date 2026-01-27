#include "DeckLoader.hpp"
#include "Joueur.hpp"
#include <iostream>

int main() {
    auto deck1 = DeckLoader::chargerDeck("pokemon.json", "trainers.json", 14, 6);
    auto deck2 = DeckLoader::chargerDeck("pokemon.json", "trainers.json", 14, 6);

    Joueur j1("Joueur 1");
    Joueur j2("Joueur 2");

    j1.initialiserDeck(std::move(deck1));
    j2.initialiserDeck(std::move(deck2));

    while (true) {
        j1.debutTour();
        j1.afficherEtat();
        j1.jouerTour(j2);
        if (j2.aPerdu()) break;

        j2.debutTour();
        j2.afficherEtat();
        j2.jouerTour(j1);
        if (j1.aPerdu()) break;
    }

    return 0;
}
