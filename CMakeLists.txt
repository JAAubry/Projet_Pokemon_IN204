cmake_minimum_required(VERSION 3.16)

project(ProjetPokemonTCG LANGUAGES CXX)

# Standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

# Exécutable
add_executable(ProjetPokemonTCG
    src/main.cpp

    src/core/Game.cpp

    src/scene/MenuScene.cpp
    src/scene/GameScene.cpp

    src/view/CarteView.cpp
    src/view/ButtonView.cpp
)

# Includes
target_include_directories(ProjetPokemonTCG
    PRIVATE
        src
        assets
)

# SFML obligatoires
target_link_libraries(ProjetPokemonTCG
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

# Le programme va chercher à charger les éléments qui sont dans le dossier d'execution
file(COPY ${CMAKE_SOURCE_DIR}/assets
     DESTINATION ${CMAKE_BINARY_DIR})

