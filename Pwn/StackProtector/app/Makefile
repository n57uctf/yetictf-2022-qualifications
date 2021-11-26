FLAGS := -fno-stack-protector -w -no-pie -m32
CC := gcc

#gcc -m32 main.c -o test -fno-stack-protector -w -no-pie

SOURCES := src/main.c

.PHONY: all docker

all: $(SOURCES)
	$(CC) $(SOURCES) -o bin/stack_protector $(FLAGS)

docker:
	$(CC) /main.c -o /stack_protector $(FLAGS)
