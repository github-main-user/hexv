#include <stdint.h>
#include <curses.h>

#define BYTES_WIDTH 16

WINDOW *line_win;
WINDOW *hex_win;
WINDOW *ascii_win;

void curses_init()
{
	initscr();
	curs_set(0);
	start_color();
	noecho();


	hex_win = newwin(LINES-2, BYTES_WIDTH * 3 , 1, 3);

	refresh();
}

void set_hex_text(uint8_t *bytes, int size)
{
	for (int i = 0; i < size; ++i)
	{
		wprintw(hex_win, "%02x ", bytes[i]);	
	}
	wrefresh(hex_win);
}

void curses_exit(void)
{
	delwin(hex_win);

	curs_set(1);
	endwin();
}

void wait_key()
{
	getch();
}
