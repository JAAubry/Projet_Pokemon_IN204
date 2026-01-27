#pragma once

#include <vector>
#include <memory>
#include <string>

#include "CarteBase.hpp"
#include "CartePokemon.hpp"
#include "CarteDresseur.hpp"

class DeckLoader {
public:
    // Charge toutes les cartes depuis les fichiers JSON
    static std::vector<std::unique_ptr<CarteBase>>
    chargerDeck(
        const std::string& fichierPokemon,
        const std::string& fichierDresseur,
        int nbPokemon,
        int nbDresseurs
    );
};
