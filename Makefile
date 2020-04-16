CC = clang++
CFLAGS = -std=c++17 -pedantic -Wall

.PHONY: all clean
all: rlsnake

rlsnake: *pp
	$(CC) $(CFLAGS) *.cpp -o RLSnake

clean: 
	rm -Rf *.dSYM RLSnake
