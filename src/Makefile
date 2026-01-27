# ==========================
# COMPILATEUR & OPTIONS
# ==========================
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# ==========================
# FICHIERS
# ==========================
SRC = \
    CartePokemon.cpp \
    CarteDresseur.cpp \
    Joueur.cpp \
    DeckLoader.cpp \
    Jeu.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = jeu

# ==========================
# REGLES
# ==========================

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
