cmake_minimum_required(VERSION 3.16)

project(ProjetPokemonTCG LANGUAGES CXX)

find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## EXECUTABLE PRINCIPAL
add_executable(ProjetPokemonTCG
    src/main.cpp
)
# Headers
target_include_directories(ProjetPokemonTCG PRIVATE include)
target_link_libraries(ProjetPokemonTCG
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

## EXECUTABLE POUR LES ESSAIS GRAPHIQUES
add_executable(GraphiqueEssai
    graphics/GraphiqueEssai.cpp
)
# Headers
target_include_directories(GraphiqueEssai PRIVATE include)
target_link_libraries(GraphiqueEssai
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

# Copie des assets dans le dossier de build
# Comme on execute dans le fichier build, il doit y être
configure_file(
    ${CMAKE_SOURCE_DIR}/assets/cards_debut.json
    ${CMAKE_BINARY_DIR}/cards_debut.json
    COPYONLY
)
configure_file(
    ${CMAKE_SOURCE_DIR}/assets/textures/fond_pokemon.jpg
    ${CMAKE_BINARY_DIR}/fond_pokemon.jpg
    COPYONLY
)
configure_file(
    ${CMAKE_SOURCE_DIR}/assets/textures/dos_carte.jpg
    ${CMAKE_BINARY_DIR}/dos_carte.jpg
    COPYONLY
)

