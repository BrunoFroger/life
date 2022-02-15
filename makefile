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

obj/%.o: src/%.cpp
	@echo "compilation de $<"
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm  -f $(OBJDIR)*.o
	@rm  -f $(EXEC)
	@echo "clean effectue"
	@make