#include <ncurses.h>
#include <unistd.h>
int     main(void)
{

	initscr();
	raw();

	start_color();
	init_pair( 1, COLOR_WHITE,   COLOR_BLACK);
	init_pair( 2, COLOR_BLACK,    COLOR_WHITE);

	WINDOW *map;
	WINDOW *side;

	side = newwin(64, 64, 1, 194);
	map = newwin(64, 192, 1, 1);

	box(map,0,0);
	box(side,0,0);
	wbkgd(map, COLOR_PAIR(1));
	wbkgd(side, COLOR_PAIR(1));

	refresh();
	wrefresh(map);
	wrefresh(side);

	for (int i = 65; i < 91; ++i) {
		wclear(map);
		wprintw(map, "%c", i);
		wrefresh(map);
		usleep(100000);
	}

	getch();
	endwin();

	return (0);
}
