#include <stdint.h>
#include <stdlib.h>

void curses_init(void);
void curses_exit(void);
void set_hex_text(uint8_t *text, int size);
void wait_key(void);

uint8_t *get_bytes(char *name);

extern int size;

int main(int argc, char **argv)
{
	uint8_t *bytes = NULL;

	curses_init();	


	if (argc == 2)
		bytes = get_bytes(argv[1]);
	

	if (bytes != NULL)
	{
		set_hex_text(bytes, size);
		free(bytes);

		wait_key();
	}
	
	curses_exit();

	
	return 0;
}
