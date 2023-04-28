#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>

#define BYTES_WIDTH 16
#define ADDR_LENGTH 8

extern int get_file_size(void);

static WINDOW *addr_pad, *hex_pad, *ascii_pad;
static int curr_y = 0;
static int max_lines;

void curses_init()
{
	initscr();
	curs_set(0);
	start_color();
	noecho();
	keypad(stdscr, TRUE);

	max_lines = get_file_size() / BYTES_WIDTH;
	
	//addr_pad =  newpad(LINES, ADDR_LENGTH,     0, 0);
	//hex_pad =   newpad(LINES, BYTES_WIDTH * 3, 0, ADDR_LENGTH + 2);
	//ascii_pad = newpad(LINES, BYTES_WIDTH,     0, (ADDR_LENGTH + 2) + (BYTES_WIDTH * 3) + 1);

	addr_pad =  newpad(max_lines, ADDR_LENGTH);
    hex_pad =   newpad(max_lines, BYTES_WIDTH * 3);
    ascii_pad = newpad(max_lines, BYTES_WIDTH);

	refresh();
}

void fill_all_pads(uint8_t *bytes, int size)
{
	int i;

	for (i = 0; i < size; i += BYTES_WIDTH)
		wprintw(addr_pad, "%08x", i);

	for (i = 0; i < size; ++i)
		wprintw(hex_pad, "%02x ", bytes[i]);	

	for (i = 0; i < size; ++i)
		wprintw(ascii_pad, "%c", (bytes[i] > 32 && bytes[i] < 128) ? bytes[i] : '.');


	wrefresh(hex_pad);
	wrefresh(ascii_pad);
	wrefresh(addr_pad);
}

void curses_exit(void)
{
	delwin(addr_pad);
	delwin(hex_pad);
	delwin(ascii_pad);

	curs_set(1);
	endwin();
}

static void scroll_all_wins(int key, int direction)
{
	curr_y += direction;

	prefresh(addr_pad,  curr_y, 0, 0, 0, max_lines, ADDR_LENGTH);
	prefresh(hex_pad,   curr_y, 0, 0, ADDR_LENGTH + 2, max_lines, BYTES_WIDTH);
	prefresh(ascii_pad, curr_y, 0, 0, (ADDR_LENGTH + 2) + (BYTES_WIDTH * 3) + 1, max_lines, BYTES_WIDTH * 3);
}

void control()
{
	int key;

	while (true)
	{
		switch (key = getch())
		{
			case 'q': curses_exit(); exit(0); break;
			case 'h':
			case KEY_LEFT: break;
			case 'l':
			case KEY_RIGHT: break;
			case 'k':
			case KEY_UP: scroll_all_wins(key, 1); break;
			case 'j': 
			case KEY_DOWN: scroll_all_wins(key, -1); break;
		}
	}
}
