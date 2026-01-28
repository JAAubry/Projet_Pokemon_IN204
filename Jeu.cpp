#include "Joueur.hpp"
#include "DeckLoader.hpp"

#include <iostream>
#include <limits>

// ----------- AFFICHAGE COMPLET D'UN JOUEUR -----------
void afficherEtatComplet(const Joueur& joueur, const Joueur& adversaire) {
    std::cout << "\n";
    std::cout << "                    TOUR DE " << joueur.getNom() << "\n";

    // ----- CÔTÉ JOUEUR -----
    joueur.afficher();
    
    // ----- MAIN DÉTAILLÉE -----
    joueur.afficherMainDetaille();

    // ----- ADVERSAIRE -----
    std::cout << "ADVERSAIRE: " << adversaire.getNom() << "\n";
    
    if (adversaire.aPokemonActif()) {
        std::cout << "Pokémon actif: ";
        adversaire.getPokemonActif()->afficher();
    } else {
        std::cout << "Aucun Pokémon actif\n";
    }
    std::cout << "Banc: " << adversaire.getBanc().size() << " Pokémon\n";
}

// ----------- SAISIE SÉCURISÉE -----------
int demanderChoix(int min, int max) {
    int choix;
    while (true) {
        std::cin >> choix;
        if (!std::cin.fail() && choix >= min && choix <= max) {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Choix invalide. Entrez un nombre entre " << min << " et " << max << ": ";
    }
    return choix;
}

// ----------- MENU D'ACTION -----------
void afficherMenu() {
    std::cout << "\n                                 |\n";
    std::cout << "│       ACTIONS DISPONIBLES        │\n";
    std::cout << "|                                  |\n";
    std::cout << "│ 1. Jouer une carte               │\n";
    std::cout << "│ 2. Attacher une énergie          │\n";
    std::cout << "│ 3. Attaquer                      │\n";
    std::cout << "│ 4. Battre en retraite            │\n";
    std::cout << "│ 5. Voir l'état du jeu            │\n";
    std::cout << "│ 6. Passer le tour                │\n";
    std::cout << "|                                  |\n";
    std::cout << "Choix: ";
}

// ----------- GESTION DU REMPLACEMENT DU POKÉMON ACTIF -----------
void remplacerPokemonActif(Joueur& joueur) {
    if (joueur.getBanc().empty()) {
        std::cout << joueur.getNom() << " n'a plus de Pokémon sur le banc!\n";
        std::cout << joueur.getNom() << " ne peut plus continuer!\n";
        return;
    }
    
    std::cout << "\n" << joueur.getNom() << " doit choisir un nouveau Pokémon actif:\n";
    const auto& banc = joueur.getBanc();
    for (size_t i = 0; i < banc.size(); ++i) {
        std::cout << "[" << i << "] ";
        banc[i]->afficher();
    }
    
    std::cout << "Choisissez un Pokémon (0-" << (banc.size() - 1) << "): ";
    int choix = demanderChoix(0, banc.size() - 1);
    
    // Utiliser la retraite sans coût pour forcer le remplacement
    joueur.batterEnRetraite(choix);
}

// ----------- MAIN -----------
int main() {

    std::cout << "   JEU DE CARTES POKÉMON - VERSION 2.0  \n";

    // Création des joueurs
    std::string nom1, nom2;
    std::cout << "Nom du Joueur 1: ";
    std::getline(std::cin, nom1);
    std::cout << "Nom du Joueur 2: ";
    std::getline(std::cin, nom2);

    Joueur joueur1(nom1);
    Joueur joueur2(nom2);

    // Chargement des decks
    std::cout << "\n Chargement des decks...\n";
    
    auto deck1 = DeckLoader::chargerDeck("pokemon.json", "trainers.json", 30);
    auto deck2 = DeckLoader::chargerDeck("pokemon.json", "trainers.json", 30);

    if (deck1.empty() || deck2.empty()) {
        std::cerr << " Erreur lors du chargement des decks!\n";
        return 1;
    }

    joueur1.setDeck(std::move(deck1));
    joueur2.setDeck(std::move(deck2));

    std::cout << "\n La partie commence!\n";
    std::cout << "Chaque joueur doit placer un Pokémon actif pour commencer.\n\n";

    // Phase d'initialisation: chaque joueur place un Pokémon actif
    for (auto* joueur : {&joueur1, &joueur2}) {
        std::cout << "\n" << joueur->getNom() << ", placez votre Pokémon de départ:\n";
        joueur->afficherMainDetaille();
        
        bool pokemonPlace = false;
        while (!pokemonPlace) {
            std::cout << "Choisissez un Pokémon à jouer (index): ";
            int idx = demanderChoix(0, 99);
            
            if (idx < static_cast<int>(joueur->getMain().size())) {
                auto& carte = joueur->getMain()[idx];
                if (carte->getType() == TypeCarte::Pokemon) {
                    joueur->jouerCarte(idx);
                    pokemonPlace = true;
                } else {
                    std::cout << " Vous devez choisir un Pokémon!\n";
                }
            } else {
                std::cout << " Index invalide!\n";
            }
        }
    }

    // ----------- BOUCLE DE JEU -----------
    int tour = 1;
    while (joueur1.peutContinuer() && joueur2.peutContinuer()) {
        
        for (auto* joueur : {&joueur1, &joueur2}) {
            Joueur* adversaire = (joueur == &joueur1) ? &joueur2 : &joueur1;
            
            // Vérifier les conditions de victoire
            if (!joueur->peutContinuer()) {
                std::cout << "\n " << joueur->getNom() << " ne peut plus continuer!\n";
                break;
            }
            
            if (!adversaire->peutContinuer()) {
                std::cout << "\n" << adversaire->getNom() << " ne peut plus continuer!\n";
                break;
            }

            // Début du tour
            std::cout << "\n\n Tour " << tour << "\n";
            joueur->debutTour();
            
            // Si pas de Pokémon actif, forcer le remplacement
            if (!joueur->aPokemonActif() && !joueur->getBanc().empty()) {
                remplacerPokemonActif(*joueur);
            }
            
            // Si toujours pas de Pokémon actif, le joueur a perdu
            if (!joueur->aPokemonActif()) {
                std::cout << joueur->getNom() << " n'a plus de Pokémon!\n";
                break;
            }

            // Boucle d'actions pour ce tour
            bool tourTermine = false;
            while (!tourTermine) {
                afficherEtatComplet(*joueur, *adversaire);
                afficherMenu();

                int choix = demanderChoix(1, 6);

                switch (choix) {
                    case 1: {  // Jouer une carte
                        if (joueur->getMain().empty()) {
                            std::cout << " Votre main est vide!\n";
                            break;
                        }
                        std::cout << "Index de la carte à jouer (0-" 
                                  << (joueur->getMain().size() - 1) << "): ";
                        int idx = demanderChoix(0, joueur->getMain().size() - 1);
                        joueur->jouerCarte(idx);
                        break;
                    }
                    
                    case 2: {  // Attacher une énergie
                        joueur->ajouterEnergieActif();
                        break;
                    }
                    
                    case 3: {  // Attaquer
                        joueur->attaquer(*adversaire);
                        
                        // Si l'adversaire n'a plus de Pokémon actif, il doit en placer un
                        if (!adversaire->aPokemonActif() && !adversaire->getBanc().empty()) {
                            remplacerPokemonActif(*adversaire);
                        }
                        
                        tourTermine = true;  // Après une attaque, le tour se termine
                        break;
                    }
                    
                    case 4: {  // Battre en retraite
                        if (joueur->getBanc().empty()) {
                            std::cout << " Vous n'avez pas de Pokémon sur le banc!\n";
                            break;
                        }
                        
                        std::cout << "Choisissez un Pokémon du banc (0-" 
                                  << (joueur->getBanc().size() - 1) << "): ";
                        int idx = demanderChoix(0, joueur->getBanc().size() - 1);
                        joueur->batterEnRetraite(idx);
                        break;
                    }
                    
                    case 5: {  // Voir l'état du jeu
                        // L'état est déjà affiché, juste continuer
                        std::cout << "\n[Appuyez sur Entrée pour continuer]";
                        std::cin.ignore();
                        std::cin.get();
                        break;
                    }
                    
                    case 6: {  // Passer le tour
                        tourTermine = true;
                        break;
                    }
                }
            }
            
            joueur->finTour();
        }
        
        tour++;
    }

    // ----------- FIN DE PARTIE -----------
    std::cout << "\n\n";
    std::cout << "            FIN DE LA PARTIE              \n";

    
    if (!joueur1.peutContinuer()) {
        std::cout << joueur2.getNom() << " remporte la victoire! \n";
    } else {
        std::cout << joueur1.getNom() << " remporte la victoire! \n";
    }
    
    std::cout << "\nPartie terminée en " << tour << " tours.\n";

    return 0;
}
