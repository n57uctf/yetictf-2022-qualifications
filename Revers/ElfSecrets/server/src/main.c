#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <inttypes.h>

#include "helpers.h"

static int8_t get_file_data(
		const char  * fname,
		file_data_t * fdata)
{
	int8_t rcode = -1;

	FILE * f = fopen(fname, "rb");
	if (NULL == f)
	{
		MSG_ERR("<%s> fopen(%s) failed: %s\n", __func__, fname, strerror(errno));
		goto exit;
	}

	int rc = fseek(f, 0, SEEK_END);
	if (-1 == rc)
	{
		MSG_ERR("<%s:%d> fseek() failed: %s\n", __func__, __LINE__, strerror(errno));
		goto exit;
	}

	fdata->size = ftell(f);
	if (0 == fdata->size)
	{
		MSG_ERR("<%s> ftell() failed: %s\n", __func__, strerror(errno));
		goto exit;
	}

	rc = fseek(f, 0, SEEK_SET);
	if (-1 == rc)
	{
		MSG_ERR("<%s:%d> fseek() failed: %s\n", __func__, __LINE__, strerror(errno));
		goto exit;
	}

	fdata->data = malloc(fdata->size);
	if (NULL == fdata->data)
	{
		MSG_ERR("<%s> malloc() failed: %s\n", __func__, strerror(errno));
		goto exit;
	}

	rc = fread(fdata->data, sizeof(uint8_t), fdata->size, f);
	if ((rc <= 0) || (rc > fdata->size))
	{
		MSG_ERR("<%s> fread() failed: %s\n", __func__, strerror(errno));
		goto exit;
	}

	rcode = 0;

exit:
	fclose(f);
	return rcode;
}

static void modified_elf_value(
		uint8_t        * elf_data,
		uint8_t          offset,
		const uint32_t   value,
		const uint32_t   value_size)
{
	for (int8_t i = 0; i < value_size; i++)
	{
		// byte swap
		elf_data[offset + i] = (uint8_t) (value >> (8 * i)) & 0xff;
	}
}

static void modified_elf_base(
		file_data_t * elf_base,
		uint32_t    * secret)
{
	srand(time(NULL));

	*secret = CONST_BASE;

	uint32_t value = rand() % (0xffffffff + 1 - 0x10000000) + 0x10000000;
	modified_elf_value(elf_base->data, OFFSET_1, value, 4);

	*secret ^= value;
	*secret &= CONST_AND;

	value = (rand() % (0xff00 + 1 - 0x0100) + 0x0100) & 0xff00;
	modified_elf_value(elf_base->data, OFFSET_2, value, 2);

	*secret |= value;
}

static int8_t send_flag_part(
		const file_data_t * flag,
		const uint8_t       level)
{
	uint8_t * ptr      = flag->data;
	uint8_t * last_ptr = flag->data + flag->size;

	ptr += BLOCK_SIZE * level;

	// overflow
	if (ptr > last_ptr)
	{
		MSG_ERR("<%s> Pointer is shit (%p|%p)\n", __func__, ptr, last_ptr);
		return -1;
	}
	// if last block
	else if ((ptr + BLOCK_SIZE) > last_ptr)
	{
		size_t size = last_ptr - ptr;
		SEND_DATA(ptr, size);
		return 1;
	}

	SEND_DATA(ptr, BLOCK_SIZE);

	return 0;
}

static int8_t start_game(
		const file_data_t * flag,
		file_data_t       * elf_base)
{
	uint8_t level = 0;

	while(1)
	{
		uint32_t correct_secret;

		modified_elf_base(elf_base, &correct_secret);

		SEND_DATA(elf_base->data, elf_base->size);

		uint32_t secret;
		READ_SECRET(&secret);

		if (secret == correct_secret)
		{
			int8_t rc = send_flag_part(flag, level);
			if (1 == rc)
			{
				MSG_INFO("win_game");
				return 0;
			}
			else if (-1 == rc)
			{
				MSG_ERR("<%s> send_flag_part() failed\n", __func__);
				return -1;
			}

			level++;

			continue;
		}

		MSG_INFO("incorrect");

		return 0;
	}

	return 0;
}

int main(int argc, char ** argv)
{
	file_data_t flag = {.data = NULL, .size = 0};

	int8_t rc = get_file_data(FLAG_FILE, &flag);
	if (-1 == rc)
	{
		MSG_ERR_MAIN();
		goto exit;
	}

	file_data_t elf_base = {.data = NULL, .size = 0};

	rc = get_file_data(ELF_BINARY, &elf_base);
	if (-1 == rc)
	{
		MSG_ERR_MAIN();
		goto exit;
	}

	rc = start_game(&flag, &elf_base);
	if (-1 == rc)
	{
		MSG_ERR_MAIN();
		goto exit;
	}

exit:
	free(flag.data);
	free(elf_base.data);

	return 0;
}
