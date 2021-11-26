#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define FLAG_FILE  "flag.txt"

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

void stack_protector_init()
{
	stack_protector = rand() % (0xffffffff - 0x10000000) + 0x10000000;
}

int invade()
{
	unsigned int protector = stack_protector;

	char name[BUFSIZE] = { 0 };

	printf("Stop, invader. What's your name?\n> ");

	if (!gets(name))
	{
		printf("gets failed\n");
		return -1;
	}

	printf("Hello, %s\n", name);

	if (protector != stack_protector)
	{
		printf("You won't go further!\n");
		exit(0);
	}

	printf("Welcome!\n");

	return 0;
}

int main(int argc, char ** argv)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	stack_protector_init();

	if (invade())
	{
		printf("invade failed\n");
		return -1;
	}

	return 0;
}
