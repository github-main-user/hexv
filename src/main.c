#include <stdint.h>
#include <stdlib.h>

void curses_init(void);
void curses_exit(void);
void set_addr_text(int size);
void set_hex_text(uint8_t *bytes, int size);
void set_ascii_text(uint8_t *bytes, int size);
void wait_key(void);

uint8_t *get_bytes(char *name);
int get_file_size(void);


int main(int argc, char **argv)
{
	uint8_t *bytes = NULL;

	curses_init();	


	if (argc == 2)
		bytes = get_bytes(argv[1]);
	

	if (bytes != NULL)
	{
		int size = get_file_size();

		set_addr_text(size);
		set_hex_text(bytes, size);
		set_ascii_text(bytes, size);

		wait_key();

		free(bytes);
	}
	
	curses_exit();

	
	return 0;
}
