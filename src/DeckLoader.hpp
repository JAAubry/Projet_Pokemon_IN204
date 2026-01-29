#pragma once

#include <vector>
#include <memory>
#include <string>

class CarteBase;

class DeckLoader {
public:
    static std::vector<std::unique_ptr<CarteBase>>
    chargerDeck(const std::string& fichierPokemon,
                const std::string& fichierDresseur,
                std::size_t tailleDeck);
};
