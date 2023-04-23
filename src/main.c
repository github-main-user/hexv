#include <stdint.h>
#include <stdlib.h>

void curses_init(void);
void curses_exit(void);
void set_hex_text(uint8_t *text);
void wait_key(void);

uint8_t get_bytes(char *name);

int main(int argc, char **argv)
{
	uint8_t *bytes;

	curses_init();	


	if (argc == 2)
		bytes = get_bytes(argv[1]);
	

	set_hex_text(str);
	
	wait_key();
	curses_exit();

	
	return 0;
}
