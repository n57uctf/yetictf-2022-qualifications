FLAGS := -Wall
CC := gcc

SRC_MAIN := src/MrAgent
SRC_AES  := src/AES/aes

BIN_MAIN := bin/MrAgent
BIN_AES  := bin/aes

BIN_LIBAES := bin/libaes

.PHONY: all debug clean

all: lib main.o
	$(CC) $(BIN_MAIN).o -Lbin -laes -o $(BIN_MAIN)

debug: lib main_debug.o
	$(CC) $(BIN_MAIN).o -Lbin -laes -o $(BIN_MAIN)

lib: lib.o
	ar rcs $(BIN_LIBAES).a $(BIN_AES).o

lib.o: $(SRC_AES).c $(SRC_AES).h
	$(CC) -c $(SRC_AES).c -o $(BIN_AES).o $(FLAGS)

main.o: $(SRC_MAIN).c
	$(CC) -c $(SRC_MAIN).c -o $(BIN_MAIN).o $(FLAGS)

main_debug.o: $(SRC_MAIN).c
	$(CC) -D DEBUG -c $(SRC_MAIN).c -o $(BIN_MAIN).o $(FLAGS)

clean:
	rm -f bin/*.o
