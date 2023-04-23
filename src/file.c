#include <stdlib.h>
#include <stdint.h>

static FILE *fp;
static int size;

void *get_bytes(char *name)
{
	fp = fopen(name, "rb");
	if (fp == NULL)
	{
		wprintf(stderr, "test");
		exit(1);
	}
		
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	uint8_t *bytes = malloc(size);


	fread(bytes, file_size, 1, fp);
	fclose(fp);

	return bytes;
}
