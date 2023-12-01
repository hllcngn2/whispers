#include <stdio.h>
#include <ncurses.h>

int	main(int ac, char **av){
initscr();
start_color();

fprintf(stderr, "Number of colors: %d\n", (int)COLORS);
fprintf(stderr, "Number of color pairs: %d\n", (int)COLOR_PAIRS);

endwin();
return 0;}
