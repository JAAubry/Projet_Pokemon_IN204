cmake_minimum_required(VERSION 3.16)

project(ProjetPokemonTCG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Exécutable
add_executable(ProjetPokemonTCG
    src/main.cpp
)

# Headers
target_include_directories(ProjetPokemonTCG PRIVATE include)

# Copie des données JSON dans le dossier de build
# Comme on execute dans le fichier build, il doit y être
configure_file(
    ${CMAKE_SOURCE_DIR}/data/cards_debut.json
    ${CMAKE_BINARY_DIR}/cards_debut.json
    COPYONLY
)

