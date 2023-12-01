#include <ncurses.h>
#include <stdlib.h>
//#include "whispers.h"
#define GWH 30
#define GWW 80
#define K_QUIT '0'
#define K_INV 'i'

int main(int ac, char** av){
initscr();
  cbreak(); noecho();
  curs_set(0); start_color();

  int gamewinh =LINES>GWH? GWH: LINES,
  gamewinw =LINES>GWW? GWW: COLS,
  gamewiny =(LINES-gamewinh)/2,
  gamewinx =(COLS-gamewinw)/2;
WINDOW* gamewin =newwin(gamewinh,gamewinw,gamewiny,gamewinx);
box(gamewin,0,0);
  int talkmarginleft =8,
  talkmarginbottom =2,
  talkwinh =5,
  talkwinw =gamewinw-talkmarginleft*2,
  talkwiny =gamewinh-(talkwinh+talkmarginbottom),
  talkwinx =talkmarginleft;
WINDOW* talkwin =newwin(talkwinh,talkwinw,talkwiny,talkwinx);
  int invmarginright =2,
  invmargintop =2,
  invwinh =gamewinh-invmargintop*2,
  invwinw =14,
  invwiny =gamewiny+invmargintop,
  invwinx =gamewinx+gamewinw-invwinw+invmarginright;
WINDOW* invwin =newwin(invwinh,invwinw,invwiny,invwinx);
int inv_on =0;

char c =0;
do {

switch(c){
case K_INV: if(!inv_on) inv_on =1;
	else { inv_on =0; werase(invwin); wrefresh(invwin); } break;
default: break;}


box(gamewin,0,0);
wrefresh(gamewin);
if(inv_on){
	box(invwin,0,0);
	wrefresh(invwin);}

} while((c=getch())!=K_QUIT);

  delwin(gamewin); delwin(talkwin); delwin(invwin);
endwin(); return 0;}

/*
WINDOW* win;
{ winx =x;
  winy =y;
  WINDOW* mywin =newwin();
  win =mywin;}
*/ 
