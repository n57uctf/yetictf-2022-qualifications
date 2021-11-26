#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define DEV_RANDOM "/dev/random"
#define FLAG_FILE  "/flag.txt"

#define BUFSIZE 64

unsigned int stack_protector = 0;

void print_flag()
{
	char flag[BUFSIZE] = { 0 };

	int fd = open(FLAG_FILE, O_RDONLY);
	if (-1 == fd)
	{
		printf("open '%s' failed: %s\n", FLAG_FILE, strerror(errno));
		exit(0);
	}

	int rc = read(fd, flag, sizeof(flag));
	if ((-1 == rc) || (rc > sizeof(flag)))
	{
		printf("read failed: %s\n", strerror(errno));
		goto ret;
	}

	printf("%s\n", flag);

ret:
	close(fd);
	exit(0);
}

int stack_protector_init()
{
	int ret = -1;

	int fd = open(DEV_RANDOM, O_RDONLY);
	if (-1 == fd)
	{
		printf("open '%s' failed: %s\n", DEV_RANDOM, strerror(errno));
		return ret;
	}

	int rc = read(fd, &stack_protector, sizeof(unsigned int));
	if ((-1 == rc) || (rc > sizeof(unsigned int)))
	{
		printf("read failed: %s\n", strerror(errno));
		goto error;
	}

	ret = 0;

error:
	close(fd);
	return ret;
}

int invade()
{
	unsigned int protector = stack_protector;

	char name[BUFSIZE] = { 0 };

	printf("Stop, invader. What's your name?\n> ");

	if (!gets(name))
	{
		printf("fgets failed\n");
		return -1;
	}

	printf("Hello, "); printf(name);

	if (protector != stack_protector)
	{
		printf("\nYou won't go further!\n");
		exit(0);
	}

	printf("\nWelcome!\n");

	return 0;
}

int main(int argc, char ** argv)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	if (stack_protector_init())
	{
		printf("stack_protector_init failed\n");
		return -1;
	}

	if (invade())
	{
		printf("invade failed\n");
		return -1;
	}

	return 0;
}
