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
uint32_t offsets[] = {0x2092, 0x2093, 0x2094, 0x2095, 0x2096, 0x2097, 0x03, 0x34f8, // YetiCTF{
                      0x23a, 0x458, 0x21f9, 0x36e1,                                 // th3_
                      0x37fe, 0x31d, 0x66f, 0x672, 0x21f9, 0x1021, 0x2094, 0x36e1,  // h4rd35t_
                      0x66f, 0x21f9, 0x15fe, 0x21f9, 0x66f, 0x1021, 0x21f9, 0x36e1, // r3v3r53_
                      0x1629, 0x324, 0x36e1,                                        // 1n_
                      0x2094, 0x458, 0x21f9, 0x36e1,                                // th3_
                      0x1385, 0x22b7, 0x66f, 0x319, 0x672, 0x440, 0xd1};            // w0rld}\n

void getFlag()
{
	int rcode = -1;

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

	uint8_t * data = malloc(size);
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

	for (int i = 0; i < sizeof(offsets); i++)
		printf("%c", data[offsets[i]]);

error:
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

		if (!memcmp(user_input, password, sizeof(user_input)))
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
