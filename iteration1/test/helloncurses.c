#include <ncurses.h>

int	main(int ac, char **av)
{
initscr();	//starts curses mode
cbreak();	//no buffering
noecho();
//nodelay(stdscr, TRUE);	//getch doesn't wait
curs_set(0);	//no cursor

erase();
printw("Hello ncurses!\n");
refresh();

getch();

endwin();
return 0;
}
