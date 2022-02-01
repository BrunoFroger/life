#-----------------------------------
#
#      makefile
#
#-----------------------------------



CC=gcc
#CFLAGS=-W -Wall -ansi -pedantic -Wcomment
CFLAGS=-Wall -Wextra -Werror -clang++ -std=c++11
LDFLAGS=-lc++ -lncurses
EXEC=life
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@chmod +x $(EXEC)
	@echo "executable $(EXEC) genere"
#	./$(EXEC)


%.o: %.c %.h
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf *.o
	@rm -rf $(EXEC)
	@echo "clean effectue"
	make