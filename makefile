#-----------------------------------
#
#      makefile
#
#-----------------------------------



CC=gcc
SRCDIR= src/
OBJDIR = obj/
INCDIR = inc/
CFLAGS=-Wall -Wextra -Werror -std=c++11
LDFLAGS=-lc++ -lncurses
SRC = $(wildcard src/*.cpp)
TMP=$(patsubst %.cpp, %.o, $(SRC))
OBJ=$(patsubst src/%.o, obj/%.o, $(TMP))
EXEC=life

ALL : $(EXEC)

$(EXEC) : $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@chmod +x $(EXEC)
	@echo "executable $(EXEC) genere"

obj/%.o: src/%.cpp inc/%.hpp
	@echo "compilation de $<"
	@$(CC) -o $@ -c $< $(CFLAGS)

obj/commande.o : \
	inc/variables.hpp  \
	inc/humain.hpp \
	inc/entreprise.hpp \
	inc/produit.hpp

obj/compteBancaire.o : \
	inc/variables.hpp 

obj/entreprise.o : \
	inc/variables.hpp  \
	inc/humain.hpp \
	inc/compteBancaire.hpp \
	inc/tools.hpp \
	inc/produit.hpp

obj/evolution.o : \
	inc/variables.hpp  \
	inc/humain.hpp \
	inc/tools.hpp \
	inc/commande.hpp

obj/humain.o : \
	inc/variables.hpp \
	inc/statistiques.hpp \
	inc/compteBancaire.hpp \
	inc/entreprise.hpp \
	inc/produit.hpp

obj/initMonde.o : \
	inc/variables.hpp  \
	inc/humain.hpp \
	inc/entreprise.hpp \
	inc/produit.hpp \
	inc/commande.hpp

obj/life.o : \
	inc/variables.hpp  \
	inc/statistiques.hpp \
	inc/humain.hpp \
	inc/entreprise.hpp \
	inc/produit.hpp \
	inc/commande.hpp

obj/produit.o : \
	inc/variables.hpp 

obj/statistiques.o : \
	inc/variables.hpp  \
	inc/humain.hpp \
	inc/entreprise.hpp \
	inc/compteBancaire.hpp \
	inc/produit.hpp \
	inc/commande.hpp

obj/variables.o : \
	inc/humain.hpp \
	inc/entreprise.hpp \
	inc/compteBancaire.hpp \
	inc/produit.hpp \
	inc/commande.hpp

obj/tools.o : \
	inc/variables.hpp  \
	inc/humain.hpp \
	inc/produit.hpp \
	inc/entreprise.hpp \
	inc/commande.hpp

clean:
#	@echo "OBJ = $(OBJ)"
	@rm  -f $(OBJDIR)*.o
	@rm  -f $(EXEC)
	@echo "clean effectue"
	@make