#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
using json = nlohmann::json;

struct Attaque {
    std::string nom;
    int dommage;
};

class Pokemon {
public:
    std::string nom;
    int hp_actuel;
    int hp_max;
    Attaque attaque;

    bool isKo() const { return hp_actuel <= 0; }
};



std::vector<Pokemon> loadPokemon(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Impossible d'ouvrir le fichier JSON");

    json data;
    file >> data;

    std::vector<Pokemon> pokemons;

    for (const auto& card : data) {

        // Vérifications de si ya tous les champs qu'on utilise
        if (!card.contains("name") ||
            !card.contains("hp") ||
            !card.contains("attacks") ||
            !card["attacks"].is_array() ||
            card["attacks"].empty())
        {
            continue; // on ignore cette carte
        }

        Pokemon p;
        p.nom = card["name"].get<std::string>();

        std::cout << p.nom <<std::endl ; 

        // hp est parfois une string ou un float donc on doit forcer
        p.hp_actuel = static_cast<int>(card["hp"].get<double>());
        p.hp_max = p.hp_actuel;

        const auto& atk = card["attacks"][0];
        p.attaque.nom = atk["name"].get<std::string>();
        // damage est une STRING genre "30", "", "30+" 
        std::string dmg = atk["damage"].get<std::string>();
        p.attaque.dommage = dmg.empty() ? 0 : std::stoi(dmg);

        pokemons.push_back(p);
    }

    return pokemons;
}






// VERSION QUI MARCHE PAS
// std::vector<Pokemon> loadPokemon(const std::string& path) {

//     std::ifstream file(path);
//     json data;
//     if (!file.is_open()) //vérification ouvertire
//         {throw std::runtime_error("Impossible d'ouvrir le fichier JSON");} 
//     file >> data;

//     std::vector<Pokemon> pokemons;

//     for (const auto& currentPokemon : data["pokemon"]) {
//         if(currentPokemon["Supertype"] == "Pokemon") { //BdD a d'autres types de carte
//             Pokemon pokemon;
//             pokemon.nom = currentPokemon["name"];
//             pokemon.hp_actuel = currentPokemon["hp"];
//             pokemon.hp_max = currentPokemon["hp"];
//             pokemon.attaque = {
//                 currentPokemon["attaque"]["nom"],
//                 currentPokemon["attaque"]["dommage"]
//             };

//             pokemons.push_back(pokemon);
//         }
//     std::cout << "apres oteration" << std::endl ;
//     }
//     return pokemons;
// }





