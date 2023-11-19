#include <ncurses.h>
int	main(int ac, char **av){
int	i;
initscr();
start_color();

for(i=0; i<8; i++){
init_pair(i, COLOR_BLACK, i);
attron(COLOR_PAIR(i));
printw(" %03d ", i);}

printw("\n");

for(; i<16; i++){
init_pair(i, COLOR_BLACK, i);
attron(COLOR_PAIR(i));
printw(" %03d ", i);}

printw("\n");

for(; i<232; i++){
if((i-16)%6==0) printw("\n");
init_pair(i, COLOR_BLACK, i);
attron(COLOR_PAIR(i));
printw(" %03d ", i);}

printw("\n");

for(; i<256; i++){
init_pair(i, COLOR_BLACK, i);
attron(COLOR_PAIR(i));
printw(" %03d ", i);
if(!(i%8)) printw("\n");}

getch();
endwin();
return 0;}
