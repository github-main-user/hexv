#include <stdint.h>
#include <stdlib.h>

void curses_init(void);
void curses_exit(void);
void set_hex_text(char *text);
void wait_key(void);

void get_bytes(char *name)

int main(int argc, char **argv)
{
	curses_init();	

	if (argc == 2)
		get_bytes(argv[1]);

	set_hex_text(str);
	
	wait_key();
	curses_exit();

	
	return 0;
}
