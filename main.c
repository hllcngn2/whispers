#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
//#include "whispers.h"
#define GWH 30
#define GWW 80
#define K_QUIT	'0'
#define K_INV	'i'
#define K_JUMP	'w'
#define K_LEFT	'a'
#define K_RIGHT	'd'
#define WHISP_INTERVAL 10
#define WHISP_DURATION 5
#define CHUNKH 60
#define CHUNKW 140
typedef struct Chunk {
	struct Chunk* left;
	struct Chunk* right;
	struct Chunk* top;
	struct Chunk* bottom;
	char** map;
} Chunk;
Chunk* newchunk(void);
void freechunks(Chunk* level);


int main(int ac, char** av){
srand(time(NULL));
initscr();
  cbreak(); noecho();
  curs_set(0); start_color();
  refresh();

  int gamewinh =LINES>GWH? GWH: LINES,
  gamewinw =COLS>GWW? GWW: COLS,
  gamewiny =(LINES-gamewinh)/2,
  gamewinx =(COLS-gamewinw)/2;
WINDOW* gamewin =newwin(gamewinh,gamewinw,gamewiny,gamewinx);
  int invmarginright =2,
  invmargintop =2,
  invwinh =gamewinh-invmargintop*2,
  invwinw =14,
  invwiny =gamewiny+invmargintop,
  invwinx =gamewinx+gamewinw-invwinw+invmarginright;
WINDOW* invwin =newwin(invwinh,invwinw,invwiny,invwinx);
int inv_on =0;
  int talkmarginleft =8,
  talkmarginbottom =-1,
  talkwinh =5,
  talkwinw =gamewinw-talkmarginleft*2,
  talkwiny =gamewiny+gamewinh-talkwinh-talkmarginbottom,
  talkwinx =gamewinx+talkmarginleft;
WINDOW* talkwin =newwin(talkwinh,talkwinw,talkwiny,talkwinx);

Chunk* level =newchunk();

char c =0;
int count =0, jump =0;
//int posy =15, posx =40;
do { count++;

switch(c){
case K_INV:	if(!inv_on) inv_on =1;
		else { inv_on =0; werase(invwin); wrefresh(invwin); } break;
//case K_LEFT:	if(
	default: break;}

if(count==WHISP_INTERVAL+WHISP_DURATION){
werase(talkwin); wrefresh(talkwin); count =0;}
box(gamewin,0,0);
mvwaddch(gamewin,gamewinh/2,gamewinw/2,'@');
wrefresh(gamewin);
if(count>=WHISP_INTERVAL){
box(talkwin,0,0);
wrefresh(talkwin);}
if(inv_on){
box(invwin,0,0);
mvwprintw(invwin,1,2,"INVENTORY");
wrefresh(invwin);}

} while((c=getch())!=K_QUIT);
freechunks(level);
  delwin(gamewin); delwin(talkwin); delwin(invwin);
endwin(); return 0;}

/*
WINDOW* win;
{ winx =x;
  winy =y;
  WINDOW* mywin =newwin();
  win =mywin;}
*/ 
Chunk* newchunk(void){
Chunk* new =(Chunk*)malloc(sizeof(Chunk));
new->map =(char**)malloc(sizeof(char*)*CHUNKH);
for(int i=0;i<CHUNKH;i++)
	new->map[i] =(char*)malloc(CHUNKW);
new->left =NULL;
new->right =NULL;
new->top =NULL;
new->bottom =NULL; return new;}

void freechunks(Chunk* level){
if(level==NULL) return;
if(level->map==NULL) return;
for(int i=0;i<CHUNKH;i++)
	free(level->map[i]);
free(level->map);
level->map =NULL;
freechunks(level->left);
freechunks(level->right);
freechunks(level->top);
freechunks(level->bottom);
free(level); return;}
