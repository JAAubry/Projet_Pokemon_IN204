#include "joueur.hpp"
#include "Carte.hpp"
#include "Dresseur.hpp"
#include "Deckloader.cpp"
int main() {
    auto poolPokemon = chargerTousLesPokemon("assets/pokemon.json");

    auto deck1 = creerDeckPokemon(poolPokemon);
    auto deck2 = creerDeckPokemon(poolPokemon);

    Joueur joueur1("Sacha", {}, deck1);
    Joueur joueur2("Pierre", {}, deck2);

    joueur1.initialiserPioche(deck1);
    joueur2.initialiserPioche(deck2);

    joueur1.piocher(5);
    joueur2.piocher(5);

    joueur1.afficherEtat();
    joueur2.afficherEtat();
}
