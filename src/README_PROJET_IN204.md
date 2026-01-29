# PROJET IN204 - POKEMON TCG POCKET SIMPLIFIE

## DESCRIPTION DU PROJET

Ce projet consiste a realiser une version simplifiee du jeu mobile Pokemon TCG Pocket en appliquant les notions de programmation orientee objet vues en cours d'IN204.

Le jeu est developpe en C++17 et utilise des concepts avances tels que le polymorphisme, l'heritage, l'encapsulation et la gestion automatique de la memoire avec les smart pointers.

## REGLES DU JEU

### Configuration de Base
- Chaque joueur possede un deck de 30 cartes (modifiable)
- Chaque joueur commence avec 7 cartes en main
- Chaque joueur a 1 Pokemon Actif en jeu
- Chaque joueur peut avoir jusqu'a 5 Pokemon sur le banc (reserve)
- La main est limitee a 10 cartes maximum

### Deroulement d'un Tour
1. **Pioche obligatoire** : Le joueur pioche 1 carte au debut de son tour
2. **Phase d'actions** (dans n'importe quel ordre) :
   - Jouer des cartes Pokemon (placer sur le terrain ou le banc)
   - Jouer des cartes Dresseur (avec restrictions selon le type)
   - Attacher 1 energie a un Pokemon (1 fois par tour maximum)
   - Battre en retraite (echanger le Pokemon actif avec un du banc)
3. **Phase d'attaque** : Attaquer le Pokemon adverse (termine le tour)

### Systeme d'Energie
- Chaque joueur peut attacher 1 energie par tour a son Pokemon actif
- Les energies sont necessaires pour :
  - Attaquer (cout variable selon le Pokemon)
  - Battre en retraite (cout variable selon le Pokemon)
- Les energies sont de type neutre (pas de types elementaires differencies)

### Conditions de Victoire
Un joueur gagne quand l'adversaire :
- N'a plus de Pokemon actif ET ne peut en placer aucun depuis son banc
- Ne peut plus piocher de carte (deck vide)
- A perdu tous ses Pokemon disponibles

### Simplifications par Rapport au Jeu Original
Pour faciliter l'implementation, certaines fonctionnalites ont ete retirees :
- **Pas de types d'energie differencies** : Toutes les energies sont neutres
- **Une seule attaque par Pokemon** : Seule la premiere attaque du JSON est chargee
- **Pas d'evolution** : Les Pokemon n'evoluent pas pendant la partie
- **Pas d'etats speciaux** : Pas de poison, paralysie, sommeil, brulure, confusion
- **Pas de capacites speciales** : Les abilities Pokemon ne sont pas implementees
- **Pas de cartes recompense** : Systeme de Prize Cards non implemente

Cependant, le jeu inclut :
- **Systeme de faiblesses** : Les Pokemon de type faible subissent le double de degats
- **Systeme de retraite** : Possibilite de changer de Pokemon actif contre energie
- **Cartes Dresseur fonctionnelles** : Effets de soins, pioche, etc.
- **Gestion complete des PV** : Soins limites au PV maximum

## ARCHITECTURE DU PROJET

### Structure des Fichiers

```
Projet IN204 Pokemon TCG
|
+-- CarteBase.hpp              Classe abstraite de base pour toutes les cartes
|
+-- CartePokemon.hpp/cpp       Implementation des cartes Pokemon
|                              (PV, energie, attaques, type, faiblesse)
|
+-- CarteDresseur.hpp/cpp      Implementation des cartes Dresseur
|                              (Objet, Supporter, effets speciaux)
|
+-- Joueur.hpp/cpp             Gestion complete d'un joueur
|                              (deck, main, Pokemon actif, banc, actions)
|
+-- DeckLoader.hpp/cpp         Chargement des decks depuis fichiers JSON
|                              Parsing et creation des cartes
|
+-- Jeu.cpp                    Boucle principale du jeu
|                              Interface utilisateur et mecanique de jeu
|
+-- Makefile                   Script de compilation
|
+-- pokemon.json               Base de donnees de 286 cartes Pokemon
+-- trainers.json              Base de donnees de 14 cartes Dresseur
```


## CLASSES PRINCIPALES

### CarteBase (Abstraite)
Classe de base definissant l'interface commune pour toutes les cartes.
- Methodes virtuelles pures : `getType()`, `getNom()`
- Methode virtuelle avec implementation par defaut : `appliquerEffet()`

### CartePokemon
Represente une carte Pokemon avec :
- **Attributs** : nom, type elementaire, PV, PV max, energie, degats, couts
- **Methodes principales** :
  - `attaquer()` : Inflige des degats (x2 si faiblesse)
  - `soigner()` : Restaure des PV (limite au max)
  - `recevoirDegats()` : Reduit les PV
  - `peutAttaquer()` : Verifie si assez d'energie
  - `peutRetraite()` : Verifie si peut battre en retraite
  - `estKO()` : Verifie si PV <= 0

### CarteDresseur
Represente une carte Dresseur avec effets speciaux.
- **Types** : Objet (sans restriction) ou Supporter (1 par tour)
- **Effets implementes** :
  - Potion : Soigne 20 PV
  - Professor's Research : Pioche 2 cartes
  - Brock : Ajoute 1 energie
  - Erika : Soigne 50 PV
  - Et autres...

### Joueur
Gere l'integralite de l'etat et des actions d'un joueur.
- **Collections** :
  - Deck (pioche)
  - Main (10 cartes max)
  - Pokemon actif
  - Banc (5 Pokemon max)
- **Actions** :
  - `piocher()` : Pioche avec limite de main
  - `jouerCarte()` : Joue Pokemon ou Dresseur
  - `attaquer()` : Attaque l'adversaire
  - `batterEnRetraite()` : Change Pokemon actif
  - `ajouterEnergieActif()` : Attache energie (1/tour)

### DeckLoader
Charge les decks depuis les fichiers JSON.
- Lit les fichiers `pokemon.json` et `trainers.json`
- Parse les donnees avec la bibliotheque nlohmann/json
- Cree les objets CarteBase correspondants
- Retourne un deck melange

## FICHIERS JSON

### pokemon.json
Contient 286 cartes Pokemon avec leurs caracteristiques completes :
- Nom, type elementaire, PV
- Attaques avec couts et degats
- Cout de retraite
- Faiblesse
- Niveau d'evolution

### trainers.json
Contient 14 cartes Dresseur avec leurs effets :
- Nom, type (Item/Supporter)
- Description de l'effet
- Parametres de l'effet

## PREREQUIS TECHNIQUES

### Logiciels Necessaires
- **Compilateur C++17** ou superieur (g++, clang++)
- **Make** pour la compilation
- **Bibliotheque nlohmann/json** pour le parsing JSON

## COMPILATION ET EXECUTION

### Compilation

```bash
# Compiler le projet
make

# Nettoyer les fichiers objets
make clean

# Recompiler completement
make clean && make
```

### Execution

```bash
# S'assurer que les fichiers JSON sont presents
ls pokemon.json trainers.json

# Lancer le jeu
./jeu
```


## FONCTIONNALITES IMPLEMENTEES

### Systeme de Combat
- Attaques avec verification du cout en energie
- Calcul des degats avec bonus de faiblesse (x2)
- Gestion des KO avec remplacement automatique
- Verification des conditions de victoire

### Systeme de Retraite
- Possibilite de changer de Pokemon actif
- Cout en energie variable selon le Pokemon
- Paiement automatique du cout
- Echange avec un Pokemon du banc

### Gestion des Cartes
- Pioche avec limite de main (10 cartes)
- Placement des Pokemon (actif ou banc)
- Application des effets des cartes Dresseur
- Restriction des Supporters (1 par tour)

### Gestion des Ressources
- Attachement d'energie (1 par tour)
- Soins avec limite au PV maximum
- Banc limite a 3 Pokemon
- Deck qui s'epuise progressivement

## MECANIQUE DE JEU

### Initialisation
1. Saisie des noms des joueurs
2. Chargement des decks (30 cartes par defaut)
3. Melange automatique des decks
4. Pioche initiale de 7 cartes
5. Placement des Pokemon actifs

### Gestion des KO
Quand un Pokemon est mis KO :
1. Le Pokemon est retire du jeu
2. Le joueur doit choisir un remplacant depuis son banc
3. Si le banc est vide, le joueur perd la partie

## AUTEURS

Projet realise dans le cadre du cours IN204 - Programmation Orientee Objet par Julie Aubry et Paul-Henri Djoko

---
**Date :** Janvier 2025
**Langage :** C++17
