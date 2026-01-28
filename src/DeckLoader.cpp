#include "DeckLoader.hpp"
#include "CartePokemon.hpp"
#include "CarteDresseur.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

std::vector<std::unique_ptr<CarteBase>>
DeckLoader::chargerDeck(const std::string& fichierPokemon,
                        const std::string& fichierDresseur,
                        std::size_t tailleDeck) {

    std::vector<std::unique_ptr<CarteBase>> deck;

    // =====================
    // Chargement Pokémon
    // =====================
    std::ifstream fpkm(fichierPokemon);
    if (!fpkm) {
        std::cerr << "Erreur : impossible d'ouvrir " << fichierPokemon << '\n';
        return deck;
    }

    json jpokemon;
    fpkm >> jpokemon;

    for (const auto& p : jpokemon) {
        if (deck.size() >= tailleDeck) break;

        // Extraction des données complètes
        std::string nom = p.value("name", "Pokemon");
        std::string type = p.value("type", "Colorless");
        int hp = p.value("hp", 60);
        std::string faiblesse = p.value("weakness", "");
        int retreatCost = p.value("retreat_cost", 1);
        
        // Extraction de l'attaque (on prend la première attaque disponible)
        int damage = 20;  // Valeur par défaut
        int attackCost = 1;  // Valeur par défaut
        
        if (p.contains("attacks") && p["attacks"].is_array() && !p["attacks"].empty()) {
            const auto& firstAttack = p["attacks"][0];
            
            // Récupérer les dégâts
            if (firstAttack.contains("damage") && !firstAttack["damage"].is_null()) {
                damage = firstAttack["damage"];
            } else {
                damage = 0;  // Attaque sans dégâts
            }
            
            // Calculer le coût total en énergie (somme de toutes les énergies requises)
            if (firstAttack.contains("cost") && firstAttack["cost"].is_object()) {
                attackCost = 0;
                for (auto& [key, val] : firstAttack["cost"].items()) {
                    attackCost += val.get<int>();
                }
                if (attackCost == 0) attackCost = 1;  // Au moins 1 énergie
            }
        }

        deck.push_back(std::make_unique<CartePokemon>(
            nom,
            type,
            hp,
            damage,
            attackCost,
            retreatCost,
            faiblesse
        ));
    }

    // =====================
    // Chargement Dresseurs
    // =====================
    std::ifstream fd(fichierDresseur);
    if (!fd) {
        std::cerr << "Erreur : impossible d'ouvrir " << fichierDresseur << '\n';
        return deck;
    }

    json jdresseur;
    fd >> jdresseur;

    for (const auto& d : jdresseur) {
        if (deck.size() >= tailleDeck) break;

        std::string type = d.value("type", "Item");

        TypeDresseur t;
        if (type == "Supporter" || type == "supporter") {
            t = TypeDresseur::Supporter;
        } else {
            t = TypeDresseur::Objet;
        }

        deck.push_back(std::make_unique<CarteDresseur>(
            d.value("name", "Dresseur"),
            t
        ));
    }

    std::cout << "Deck chargé: " << deck.size() << " cartes\n";
    
    return deck;
}
