#include <stdint.h>
#include <stdlib.h>
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

	
	addr_win =  newwin(LINES, LINE_WIDTH,      0, 0);
	hex_win =   newwin(LINES, BYTES_WIDTH * 3, 0, LINE_WIDTH + 2);
	ascii_win = newwin(LINES, BYTES_WIDTH,     0, (LINE_WIDTH + 2) + (BYTES_WIDTH * 3) + 1);

	scrollok(addr_win, TRUE);
	scrollok(hex_win, TRUE);
	scrollok(ascii_win, TRUE);


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

void set_ascii_text(uint8_t *bytes, int size)
{
	for (int i = 0; i < size; ++i)
		wprintw(ascii_win, "%c", (bytes[i] > 32 && bytes[i] < 128) ? bytes[i] : '.');

	wrefresh(ascii_win);
}

void curses_exit(void)
{
	delwin(addr_win);
	delwin(hex_win);
	delwin(ascii_win);

	curs_set(1);
	endwin();
}

void control()
{
	char key;

	while (true)
	{
		switch (key = getch())
		{
			case 'q': curses_exit(); exit(0); break;
		}
	}
}
