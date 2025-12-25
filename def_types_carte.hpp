#include <nlohmann/json.hpp> // pour manipuler JSON
#include <string>
#include <iostream>

enum Statut_Utilisation {
        pioche,
        main,
        banc,
        active,
        deja_utilisee
};

enum Element {
    Normal,
    Feu,
    Eau,
    Plante,
    Electrik,
    Glace,
    Combat,
    Poison,
    Sol,
    Vol,
    Psy,
    Insecte,
    Roche,
    Spectre,
    Dragon,
    Tenebres,
    Acier,
    Fee
} ;

class Carte {
    // on devra sûrement rajouter des champs d'objet graphique
    protected :
    std::string id ;
    std::string nom ;
    std::string url_image ;
    Statut_Utilisation statut ;

    public :
    
} ;

void chargerJson(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Impossible d'ouvrir le fichier JSON: " + path);
        }

        nlohmann::json j;
        file >> j;

        // Recupere les valeurs ou par défaut si donnée manquante
        name      = j.value("name","nom inconnu") ;
};
