#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define PASS_SIZE 38

#define HARDEST_PATH "./hardest"

uint8_t getRandomNumber(uint8_t min, uint8_t max) {
	return rand() % (max - min + 1) + min;
}

// YetiCTF{th3_h4rd35t_r3v3r53_1n_th3_w0rld}
uint32_t offsets[] = {0x2092, 0x2093, 0x2094, 0x2095, 0x2096, 0x2097, 0x0003, 0x30c8, // YetiCTF{
                      0x023a, 0x0208, 0x21f9, 0x069e,                                 // th3_
                      0x0208, 0x032d, 0x0687, 0x023b, 0x21f9, 0x1021, 0x2094, 0x069e, // h4rd35t_
                      0x0687, 0x21f9, 0x0668, 0x21f9, 0x0687, 0x1021, 0x21f9, 0x069e, // r3v3r53_
                      0x10eb, 0x0324, 0x069e,                                         // 1n_
                      0x023a, 0x0208, 0x21f9, 0x69e,                                  // th3_
                      0x13a5, 0x01a0, 0x0687, 0x031f, 0x0672, 0x0320, 0x458, 0x7b};   // w0rld}\n

#define OFFSETS_SIZE sizeof(offsets)/sizeof(offsets[0]) - 1

void getFlag()
{
	int rcode = -1;

	uint8_t * data = NULL;

	FILE * f = fopen(HARDEST_PATH, "rb");
	if (!f)
	{
		fprintf(stderr, "fopen(%s) failed: %s\n", HARDEST_PATH, strerror(errno));
		exit(-1);
	}

	int rc = fseek(f, 0, SEEK_END);
	if (-1 == rc)
	{
		fprintf(stderr, "fseek() failed: %s\n", strerror(errno));
		goto error;
	}

	long size = ftell(f);
	if (0 == size)
	{
		fprintf(stderr, "ftell() failed: %s\n", strerror(errno));
		goto error;
	}

	rc = fseek(f, 0, SEEK_SET);
	if (-1 == rc)
	{
		fprintf(stderr, "fseek() failed: %s\n", strerror(errno));
		goto error;
	}

	data = malloc(size);
	if (!data)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		goto error;
	}

	rc = fread(data, sizeof(uint8_t), size, f);
	if ((rc <= 0) || (rc > size))
	{
		fprintf(stderr, "fread() failed: %s\n", strerror(errno));
		goto error;
	}

	for (int i = 0; i < OFFSETS_SIZE; i++)
		printf("%c", data[offsets[i]]);

error:
	free(data);
	fclose(f);
}

int main()
{
	srand(time(NULL));

	uint8_t user_input[PASS_SIZE] = { 0 };
	uint8_t password[PASS_SIZE]   = { 0 };

	printf("Hello. Welcome to YetiCTF!\n"
	       "I hope you remember your password... Because it is very HARD! ");

	while (1)
	{
		printf("\nGive me your HARD password: ");

		for (int i = 0; i < sizeof(password) - 1; i++)
		{
			password[i] = getRandomNumber(0x41, 0x7a);
		}

		if (!fgets((char* )user_input, sizeof(user_input), stdin))
		{
			fprintf(stderr, "fgets failed: %s\n", strerror(errno));
			exit(-1);
		}

		if (!memcmp(user_input, password, sizeof(user_input) - 1))
		{
			getFlag();
			return 0;
		}

		printf("\nNop. Try again?\n"
		       "Press F to exit or another symbol to continue: ");

		char choise = (char) getchar();

		if (choise == 'F' || choise == 'f')
			break;
	}

	return 0;
}
