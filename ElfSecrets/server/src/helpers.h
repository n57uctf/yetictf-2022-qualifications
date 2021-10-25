#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#define ELF_SIZE       238
#define BLOCK_SIZE     1024
#define ELF_VALUE_SIZE 4

#define CONST_BASE 0xaabbccdd
#define CONST_AND  0xffff00ff

#define OFFSET_1 0x7c
#define OFFSET_2 0x9b

#ifdef IN_DOCKER

#define FLAG_FILE  "flag.png"
#define ELF_BINARY "elf"

#else

#define FLAG_FILE  "./flag/flag.png"
#define ELF_BINARY "./bin/elf"

#endif // IN_DOCKER

#define SEND_DATA(__data__, __size__) write(1, __data__, __size__)

#define READ_SECRET(__buf__) read(0, __buf__, sizeof(uint32_t))

// problems with stdout in docker
#define MSG_INFO(__fmt__, ...) \
	do \
	{ \
		fprintf(stderr, __fmt__, ##__VA_ARGS__); \
	} while(0)

#define MSG_ERR(__fmt__, ...) \
	do \
	{ \
		fprintf(stderr, "[Error] - "); \
		fprintf(stderr, __fmt__, ##__VA_ARGS__); \
		fprintf(stderr, "\n"); \
	} while(0)

#define MSG_ERR_MAIN(__fmt__, ...) \
	do \
	{ \
		fprintf(stderr, "[Error] - "); \
		fprintf(stderr, __fmt__, ##__VA_ARGS__); \
		fprintf(stderr, "\nPlease, send error log to @bigger777\n"); \
	} while(0)

typedef struct file
{
	uint8_t * data;
	size_t    size;
} file_data_t;

#endif // _HELPERS_H_
