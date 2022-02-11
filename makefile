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
	@echo "debut de all"

$(EXEC) : $(OBJ)
	@echo "construction de l'executable"
	@$(CC) -o $@ $^ $(LDFLAGS)
	@chmod +x $(EXEC)
	@echo "executable $(EXEC) genere"

obj/%.o: src/%.cpp
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@echo "debut de clean"
	@rm  $(OBJDIR)*.o
	@rm  $(EXEC)
	@echo "clean effectue"