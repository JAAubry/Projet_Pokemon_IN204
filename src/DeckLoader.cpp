#include "deckloader.hpp"

#include <fstream>
#include <iostream>
#include <random>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

// ----------- utilitaire ----------
static int nombreAleatoire(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// --------------------------------
std::vector<std::unique_ptr<CarteBase>>
DeckLoader::chargerDeck(
    const std::string& fichierPokemon,
    const std::string& fichierDresseur,
    int nbPokemon,
    int nbDresseurs
) {
    std::vector<std::unique_ptr<CarteBase>> deck;

    // =====================
    // Chargement Pokémon
    // =====================
    {
        std::ifstream file(fichierPokemon);
        if (!file) {
            std::cerr << "Impossible d'ouvrir " << fichierPokemon << std::endl;
            return deck;
        }

        json data;
        file >> data;

        for (int i = 0; i < nbPokemon; ++i) {
            const auto& p = data[nombreAleatoire(0, data.size() - 1)];

            deck.push_back(std::make_unique<CartePokemon>(
                p.value("name", "Pokemon"),
                p.value("hp", 50),
                p.value("damage", 10),
                p.value("retreat", 1),
                p.value("attack_cost", 1)
            ));
        }
    }

    // =====================
    // Chargement Dresseurs
    // =====================
    {
        std::ifstream file(fichierDresseur);
        if (!file) {
            std::cerr << "Impossible d'ouvrir " << fichierDresseur << std::endl;
            return deck;
        }

        json data;
        file >> data;

        for (int i = 0; i < nbDresseurs; ++i) {
            const auto& d = data[nombreAleatoire(0, data.size() - 1)];

            TypeDresseur type =
                d.value("type", "Objet") == "Supporter"
                ? TypeDresseur::Supporter
                : TypeDresseur::Objet;

            deck.push_back(std::make_unique<CarteDresseur>(
                d.value("name", "Dresseur"),
                d.value("effect", ""),
                type
            ));
        }
    }

    return deck;
}
