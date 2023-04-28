#include <stdint.h>
#include <stdlib.h>

extern void curses_init(void);
extern void curses_exit(void);
extern void set_addr_text(int size);
extern void set_hex_text(uint8_t *bytes, int size);
extern void set_ascii_text(uint8_t *bytes, int size);
extern void control(void);

extern uint8_t *get_bytes(char *name);
extern int get_file_size(void);


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

		control();

		free(bytes);
	}
	
	curses_exit();

	
	return 0;
}
