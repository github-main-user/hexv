#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>

#define BYTES_WIDTH 16
#define ADDR_LENGTH 9

extern int get_file_size(void);

static WINDOW *addr_pad, *hex_pad, *ascii_pad;
static int curr_y = 0;
static int max_lines;

void curses_init()
{
	void init_pallete(void), print_header(void);

	initscr();
	curs_set(0);
	start_color();
	init_pallete();
	noecho();
	keypad(stdscr, TRUE);

	max_lines = get_file_size() / BYTES_WIDTH;
	
	addr_pad =  newpad(max_lines, ADDR_LENGTH);
    hex_pad =   newpad(max_lines, BYTES_WIDTH * 3);
    ascii_pad = newpad(max_lines, BYTES_WIDTH);

	print_header();
	refresh();
}

void init_pallete()
{
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
}

void print_header()
{
	int i;

	attron(COLOR_PAIR(2));

	printw("offset:   ");
	for (i = 0; i < BYTES_WIDTH; ++i)
		printw("%02x ", i);

	addch(' ');
	for (i = 0; i < BYTES_WIDTH; ++i)
		printw("%1x", i);

	attroff(COLOR_PAIR(2));
}

void refresh_all_pads()
{
	prefresh(addr_pad,  curr_y, 0, 1, 0,										 LINES - 1, ADDR_LENGTH + 1);
	prefresh(hex_pad,   curr_y, 0, 1, ADDR_LENGTH + 1,							 LINES - 1, (ADDR_LENGTH + 1) + (BYTES_WIDTH * 3));
	prefresh(ascii_pad, curr_y, 0, 1, (ADDR_LENGTH + 1) + (BYTES_WIDTH * 3) + 1, LINES - 1, (ADDR_LENGTH + 1) + (BYTES_WIDTH * 3) + BYTES_WIDTH);
}

void fill_all_pads(uint8_t *bytes, int size)
{
	int i;

	attron(COLOR_PAIR(2));
	for (i = 0; i < size; i += BYTES_WIDTH)
		wprintw(addr_pad, "%08x:", i);
	attroff(COLOR_PAIR(2));

	for (i = 0; i < size; ++i)
		wprintw(hex_pad, "%02x ", bytes[i]);	

	for (i = 0; i < size; ++i)
		wprintw(ascii_pad, "%c", (bytes[i] > 32 && bytes[i] < 128) ? bytes[i] : '.');


	refresh_all_pads();
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

	refresh_all_pads();
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
			case KEY_UP: scroll_all_wins(key, -1); break;
			case 'j': 
			case KEY_DOWN: scroll_all_wins(key, 1); break;
		}
	}
}
