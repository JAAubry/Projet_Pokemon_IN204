Ici on fera la doc <br>
lien du notion (a supprimer avant le rendu): https://www.notion.so/Projet-IN204-2ca011f9bf33800b9cb1fa8f7491c8fd?source=copy_link

Nécessite SFML version 2.6.1
linux : sudo apt-get install libsfml-dev

# Execution
## Faire suite à des modifications des fichiers
se placer à la racine
rm -rf out/build/gccJulie0126 <br>
cmake --preset gccJulie0126 <br>

se place à la racine, supprime l'ancien build, reconfigure

# Faire à chaque fois
cmake --preset gccJulie0126
cmake --build out/build/gccJulie0126 <br>
cd out/build/gccJulie0126 <br>
./ProjetPokemonTCG<br>

compile, se place dans le bon repertoire, lance l'executable<br>
