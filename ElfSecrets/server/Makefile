FLAGS := -Wall
CC := gcc

SERVER_SOURCES := src/main.c
ELF_SOURCES := src/elf.asm

.PHONY: all server_build_start elf docker_build docker_run docker_build_run in_docker help

all: $(SERVER_SOURCES)
	$(CC) $(SERVER_SOURCES) -o bin/elf-server $(FLAGS)

in_docker:
	$(CC) -D IN_DOCKER $(SERVER_SOURCES) -o bin/elf-server $(FLAGS)

elf:
	nasm -f elf32 src/elf.asm -o bin/elf.o && ld bin/elf.o -o bin/elf -m elf_i386 -n
	rm bin/elf.o
	strip bin/elf
	dd if=bin/elf of=bin/elf_mod bs=1 count=238
	mv bin/elf_mod bin/elf
	chmod +x bin/elf

docker_build:
	docker build -t elf-server .

docker_run:
	docker run -dp 8888:8888 elf-server

docker_build_run:
	docker build -t elf-server .
	docker run -i -dp 8888:8888 elf-server

help:
	@echo "help             - show help information"
	@echo "in_docker        - build for running in docker"
	@echo "all              - build for running local"
	@echo "docker_build     - build docker"
	@echo "docker_run       - run docker"
	@echo "docker_run_build - build and run docker"
