FLAGS := -Wall
CC := gcc

SOURCES := src/main.c

.PHONY: all docker

all: $(SOURCES)
	$(CC) $(SOURCES) -o bin/near $(FLAGS)

docker:
	$(CC) /main.c -o /near $(FLAGS)
