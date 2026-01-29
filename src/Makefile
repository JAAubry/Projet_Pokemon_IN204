CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I/usr/include

OBJS = \
CartePokemon.o \
CarteDresseur.o \
Joueur.o \
DeckLoader.o \
Jeu.o

jeu: $(OBJS)
	$(CXX) $(CXXFLAGS) -o jeu $(OBJS)

CartePokemon.o: CartePokemon.cpp CartePokemon.hpp CarteBase.hpp
	$(CXX) $(CXXFLAGS) -c CartePokemon.cpp

CarteDresseur.o: CarteDresseur.cpp CarteDresseur.hpp CarteBase.hpp Joueur.hpp
	$(CXX) $(CXXFLAGS) -c CarteDresseur.cpp

Joueur.o: Joueur.cpp Joueur.hpp CarteBase.hpp CartePokemon.hpp CarteDresseur.hpp
	$(CXX) $(CXXFLAGS) -c Joueur.cpp

DeckLoader.o: DeckLoader.cpp DeckLoader.hpp CartePokemon.hpp CarteDresseur.hpp
	$(CXX) $(CXXFLAGS) -c DeckLoader.cpp

Jeu.o: Jeu.cpp Joueur.hpp DeckLoader.hpp
	$(CXX) $(CXXFLAGS) -c Jeu.cpp

clean:
	rm -f *.o jeu

.PHONY: clean
