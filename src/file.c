#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

FILE *fp;
int size;

uint8_t *get_bytes(char *name)
{
	fp = fopen(name, "rb");
	if (fp == NULL)
		return NULL;

		
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);


	uint8_t *bytes = malloc(size);

	fread(bytes, size, 1, fp);
	fclose(fp);

	return bytes;
}

int get_file_size()
{
	return size;
}
