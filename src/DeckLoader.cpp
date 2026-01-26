#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json chargerJSON(const std::string& chemin) {
    std::ifstream fichier(chemin);
    if (!fichier) {
        throw std::runtime_error("Impossible d'ouvrir " + chemin);
    }
    return json::parse(fichier);
}


#include "carte.hpp"
#include <vector>

Carte creerPokemonDepuisJSON(const json& p) {
    std::string nom = p.value("name", "Pokemon inconnu");
    int pv = std::stoi(p.value("hp", "50"));

    int degats = 10;
    int coutAttaque = 1;
    int coutRetraite = 1;

    if (p.contains("attacks") && !p["attacks"].empty()) {
        const auto& attaque = p["attacks"][0];

        if (attaque.contains("damage")) {
            std::string dmg = attaque["damage"];
            if (!dmg.empty() && isdigit(dmg[0]))
                degats = std::stoi(dmg);
        }

        if (attaque.contains("cost"))
            coutAttaque = attaque["cost"].size();
    }

    if (p.contains("retreatCost"))
        coutRetraite = p["retreatCost"].size();

    return Carte(nom, pv, degats, coutRetraite, coutAttaque);
}


std::vector<Carte> chargerTousLesPokemon(const std::string& chemin) {
    json data = chargerJSON(chemin);

    std::vector<Carte> pokemons;

    for (const auto& p : data) {
        pokemons.push_back(creerPokemonDepuisJSON(p));
    }

    return pokemons;
}


#include <algorithm>
#include <random>

std::vector<Carte> creerDeckPokemon(
    const std::vector<Carte>& poolPokemon,
    int tailleDeck = 20,
    int nbPokemon = 14
) {
    std::vector<Carte> deck;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<Carte> copie = poolPokemon;
    std::shuffle(copie.begin(), copie.end(), gen);

    for (int i = 0; i < nbPokemon && i < (int)copie.size(); ++i) {
        deck.push_back(copie[i]);
    }

    // Complément avec Pokémon supplémentaires (simplification)
    while ((int)deck.size() < tailleDeck) {
        deck.push_back(copie[deck.size() % copie.size()]);
    }

    return deck;
}

std::vector<Carte> poolPokemon =
    chargerTousLesPokemon("assets/pokemon.json");

std::vector<Carte> deckJoueur1 = creerDeckPokemon(poolPokemon);
std::vector<Carte> deckJoueur2 = creerDeckPokemon(poolPokemon);


