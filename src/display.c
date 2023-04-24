#include <stdint.h>
#include <curses.h>

#define BYTES_WIDTH 16
#define LINE_WIDTH 8

WINDOW *addr_win, *hex_win, *ascii_win;

void curses_init()
{
	initscr();
	curs_set(0);
	start_color();
	noecho();

	
	addr_win = newwin(LINES-2, LINE_WIDTH, 0, 0);
	hex_win = newwin(LINES-2, BYTES_WIDTH * 3 , 0, LINE_WIDTH + 1);


	refresh();
}

void set_addr_text(int size)
{
	for (int i = 0; i < size; i += BYTES_WIDTH)
		wprintw(addr_win, "%08x", i);

	wrefresh(addr_win);
}

void set_hex_text(uint8_t *bytes, int size)
{
	for (int i = 0; i < size; ++i)
		wprintw(hex_win, "%02x ", bytes[i]);	

	wrefresh(hex_win);
}

void curses_exit(void)
{
	delwin(addr_win);
	delwin(hex_win);

	curs_set(1);
	endwin();
}

void wait_key()
{
	getch();
}
