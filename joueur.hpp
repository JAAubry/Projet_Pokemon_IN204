#pragma once
#include <string>
#include "carte.hpp"

class Joueur {
public:
    std::string Nom;
    std::vector<std::unique_ptr<Pokemon>> Active;
    std::vector<std::unique_ptr<Pokemon>> Banc;
    std::vector<std::unique_ptr<Pokemon>> Main;
};