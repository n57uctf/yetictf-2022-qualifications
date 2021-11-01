#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <ftw.h>

#include "helpers.h"

static inline void sockaddr_init(struct sockaddr_in * addr)
{
	addr->sin_family      = AF_INET;
	addr->sin_port        = htons(SERVER_PORT);
	addr->sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
}

int save_elf(const uint8_t * buffer, const uint8_t level)
{
	char * elf_fname = NULL;
	FILE * f         = NULL;

	int rc = asprintf(&elf_fname, ELF_DIR "elf%"PRIu8, level);
	if (-1 == rc)
	{
		fprintf(stderr, "internal error: %s\n", strerror(errno));
		goto _exit;
	}

	f = fopen(elf_fname, "wb");
	if (NULL == f)
	{
		fprintf(stderr, "fopen() failed: %s\n", strerror(errno));
		rc = -1;
		goto _exit;
	}

	rc = fwrite(buffer, sizeof(uint8_t), ELF_SIZE, f);
	if ((rc <= 0) || (rc > ELF_SIZE))
	{
		fprintf(stderr, "internal error: %s\n", strerror(errno));
		rc = -1;
		goto _exit;
	}

	rc = chmod(elf_fname, 0777);
	if (-1 == rc)
	{
		fprintf(stderr, "internal error: %s\n", strerror(errno));
		goto _exit;
	}

	rc = 0;
_exit:
	free(elf_fname);
	fclose(f);

	return rc;
}

int save_answer_part(const uint8_t * buffer)
{
	int rc = -1;

	FILE * f = fopen(ELF_MOM_PNG, "a");
	if (NULL == f)
	{
		fprintf(stderr, "fopen() failed: %s\n", strerror(errno));
		goto _exit;
	}

	rc = fwrite(buffer, sizeof(uint8_t), BUFSIZE, f);
	if ((rc <= 0) || (rc > BUFSIZE))
	{
		fprintf(stderr, "internal error: %s\n", strerror(errno));
		rc = -1;
		goto _exit;
	}

	rc = 0;

_exit:
	fclose(f);

	return 0;
}

int check_answer(const uint8_t * buffer)
{
	if (!strncmp((char*) buffer, INCORRECT_ANSVER, sizeof(INCORRECT_ANSVER) - 1))
	{
		printf("Wrong secret :(\n");
		return 1;
	}
	else if (!strncmp((char*) buffer, WIN_GAME_ANSWER, sizeof(WIN_GAME_ANSWER) - 1))
	{
		printf("Congratulations! You known all Elf's secrets, check it.\n");
		return 1;
	}
	else
	{
		int rc = save_answer_part(buffer);
		if (-1 == rc)
		{
			fprintf(stderr, "save_answer_part() failed\n");
			return -1;
		}
	}

	return 0;
}

int unlink_cb(const char * fpath, const struct stat * sb, int typeflag, struct FTW * ftwbuf)
{
	int rc = remove(fpath);
	if (-1 == rc)
	{
		fprintf(stderr, "internal error: %s\n", strerror(errno));
	}

	return rc;
}

int rm_rf(const char * path)
{
	return nftw(path, unlink_cb, 120, FTW_DEPTH | FTW_PHYS);
}

int main(int argc, char ** argv)
{
	// delete .png and dir
	rm_rf(ELF_MOM_PNG);
	rm_rf(ELF_DIR);

	int sock;
	struct sockaddr_in srv_addr;

	sockaddr_init(&srv_addr);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sock)
	{
		fprintf(stderr, "internal error: %s", strerror(errno));
		return -1;
	}

	int rc = connect(sock, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
	if (-1 == rc)
	{
		fprintf(stderr, "connect failed: %s\n", strerror(errno));
		return -1;
	}

	struct stat st;

	rc = stat(ELF_DIR, &st);
	if (-1 == rc)
	{
		rc = mkdir(ELF_DIR, 0700);
		if (-1 == rc)
		{
			fprintf(stderr, "internal error: %s\n", strerror(errno));
			return -1;
		}
	}

	printf("Hello. Let's play with my Elfs.\n\n");

	uint8_t level = 0;

	while(1)
	{
		printf("[Lvl %"PRIu8"] Tell me Elf's secret.\n", level);

		uint8_t buffer[BUFSIZE] = { 0 };

		// get elf
		rc = recv(sock, buffer, ELF_SIZE, MSG_WAITALL);
		if (rc < 0)
		{
			fprintf(stderr, "recv() failed: %s\n", strerror(errno));
			return -1;
		}

		rc = save_elf(buffer, level);
		if (-1 == rc)
		{
			fprintf(stderr, "save_elf() failed\n");
			return -1;
		}

		memset(buffer, 0, sizeof(buffer));

		uint32_t input;
		scanf("%"PRIu32, &input);

		rc = send(sock, &input, sizeof(uint32_t), 0);
		if (rc < 0)
		{
			fprintf(stderr, "send() failed: %s\n", strerror(errno));
			return -1;
		}

		// recv answer
		rc = recv(sock, buffer, sizeof(buffer), MSG_WAITALL);
		if (rc < 0)
		{
			fprintf(stderr, "recv() failed: %s\n", strerror(errno));
			return -1;
		}

		rc = check_answer(buffer);
		if (-1 == rc)
		{
			fprintf(stderr, "check_answer() failed\n");
			return -1;
		}
		// loose or win
		else if (1 == rc)
		{
			return 0;
		}

		level++;
	}

	return 0;
}
