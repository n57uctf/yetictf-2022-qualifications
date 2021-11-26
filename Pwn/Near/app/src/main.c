#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define FLAG_FILE  "flag.txt"

#define BUFSIZE 32

int get_flag(char * flag, size_t size)
{
	int ret = -1;

	int fd = open(FLAG_FILE, O_RDONLY);
	if (-1 == fd)
	{
		printf("open '%s' failed: %s\n", FLAG_FILE, strerror(errno));
		return -1;
	}

	int rc = read(fd, flag, size);
	if ((-1 == rc) || (rc > size))
	{
		printf("read failed: %s\n", strerror(errno));
		goto error;
	}

	ret = 0;

error:
	close(fd);
	return ret;
}

int saving(char * flag)
{
	if (NULL == flag) return -1;

	printf("It haunts me! Help get rid of him!\n> ");

	char input[BUFSIZE] = { 0 };
	
	if (!fgets(input, sizeof(input), stdin))
	{
		printf("fgets failed\n");
		return -1;
	}

	sscanf(input, "%s", flag);

	printf("Thanks. You helped me: %s\n", flag);

	sleep(2);

	return 0;
}

int fatality(char * flag)
{
	if (NULL == flag) return -1;

	printf("But now you have to finish it.\n\n"
	       "Where is his weak point?\n> ");

	int point;
	scanf("%d", &point);

	flag[point] = 'X';

	printf("%s\n", flag);

	return 0;
}

int main(int argc, char ** argv)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	char flag[BUFSIZE] = { 0 };

	if (get_flag(flag, sizeof(flag)))
	{
		printf("get_flag failed\n");
		return -1;
	}

	printf("I feel someone is watching me...\n");
	sleep(2);

	if (saving(flag))
	{
		printf("saving failed\n");
		return -1;
	}

	if (fatality(flag))
	{
		printf("fatality failed\n");
		return -1;
	}

	return 0;
}
