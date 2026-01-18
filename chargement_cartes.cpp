#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include "carte.hpp"
using json = nlohmann::json; // pour que ca soit plus concis

std::vector<Pokemon> loadPokemon(const std::string path) {
    std::iostream file(path);
    json data;
    if (!file.is_open()) //vérification ouvertire
        {throw std::runtime_error("Impossible d'ouvrir le fichier JSON");} 
    file >> data;


    std::vector<Pokemon> pokemons;

    for (const auto& currentPokemon : data["pokemon"]) {
        Pokemon pokemon;
        pokemon.nom = currentPokemon["name"];
        pokemon.hp_actuel = currentPokemon["hp"];
        pokemon.hp_max = currentPokemon["hp"];
        pokemon.attaque = {
            currentPokemon["attacks"]["name"],
            currentPokemon["attacks"]["damage"]
        };

        pokemons.push_back(pokemon);
    }

    return pokemons;
}
