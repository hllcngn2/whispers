#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>//usleep
//#include "whispers.h"
#define GWH 30
#define GWW 80
#define K_QUIT	'0'
#define K_INV	'i'
#define K_JUMP	'w'
#define K_LEFT	'a'
#define K_RIGHT	'd'
#define K_STOP	's'
#define FRAMERATE 9
#define WHISP_INTERVAL 10
#define WHISP_DURATION 5
#define CHUNKH 150
#define CHUNKW 250
#define PLTFRMWMAX 25
#define PLX(camx) camx+GWW/2
#define PLY(camy) camy+GWH/2
typedef struct Chunk {
	struct Chunk* left;
	struct Chunk* right;
	struct Chunk* top;
	struct Chunk* bottom;
	char** map;
} Chunk;
Chunk* newchunk(void);
void freechunks(Chunk* level);
void populate(Chunk* chunk);

char** get_map(void);
int get_color(char**,int,int);


int main(int ac, char** av){
srand(time(NULL));
initscr();
  cbreak(); noecho(); nodelay(stdscr,TRUE);
  curs_set(0); start_color();
  refresh();
init_pair(1, COLOR_WHITE, COLOR_BLACK);
init_pair(5, COLOR_BLACK, 213); //pink
init_pair(2, COLOR_BLACK, 99); //purple
init_pair(3, COLOR_BLACK, 177); //pink in-between
init_pair(4, COLOR_BLACK, 135); //purple in-between

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

char** cm =get_map();
Chunk* level =newchunk();
populate(level);

int camy =(CHUNKH-GWH)/2, camx =(CHUNKW-GWW)/2;
int frame =0, jump =0, dir =0;
clock_t start =clock(), end;
char c =0;
do {

switch(c){
case K_INV: if(!inv_on) inv_on =1;
	else { inv_on =0;
		werase(invwin); wrefresh(invwin); } break;
case K_LEFT:	dir =-1; break;
case K_RIGHT:	dir =1; break;
case K_STOP:	dir =0; break;
case K_JUMP:	if (!jump) jump=6;	break;
default:	break;}

if (dir==-1 && (level->map[PLY(camy)][PLX(camx)-1]<10
	|| level->map[PLY(camy)][PLX(camx)-1]=='_')){
	camx--; frame++;}
if (dir==1 && (level->map[PLY(camy)][PLX(camx)+1]<10
	|| level->map[PLY(camy)][PLX(camx)+1]=='_')){
	camx++; frame++;}
if (jump){
	if (!level->map[PLY(camy-1)][PLX(camx)]){
		camy-=1; frame++;}
	jump--;}
else if(!jump && !level->map[PLY(camy)][PLX(camx)])
	camy++;

if(frame==WHISP_INTERVAL+WHISP_DURATION){
werase(talkwin); wrefresh(talkwin); frame =0;}
wmove(gamewin,0,0);


for(int i=0;i<GWH;i++) for(int j=0;j<GWW;j++)
	if(!level->map[camy+i][camx+j]){
		wattron(gamewin,COLOR_PAIR(get_color(cm,i,j)));
		waddch(gamewin,' ');}
	else if(level->map[camy+i][camx+j]==1){
		wattron(gamewin,COLOR_PAIR(get_color(cm,i,j)));
		waddch(gamewin,' ');}
	else if(level->map[camy+i][camx+j]=='_'){
		wattron(gamewin,COLOR_PAIR(get_color(cm,i,j)));
		waddch(gamewin,' ');}
	else {	wattron(gamewin,COLOR_PAIR(1));
		mvwaddch(gamewin,i,j,level->map[camy+i][camx+j]);}
wattron(gamewin,COLOR_PAIR(1));
box(gamewin,0,0);
wattron(gamewin,COLOR_PAIR(get_color(cm,gamewinh/2,gamewinw/2)));
mvwaddch(gamewin,gamewinh/2,gamewinw/2,'@');
wrefresh(gamewin);
if(frame>=WHISP_INTERVAL){
box(talkwin,0,0);
wrefresh(talkwin);}
if(inv_on){
box(invwin,0,0);
mvwprintw(invwin,1,2,"INVENTORY");
wrefresh(invwin);}

end =clock();
usleep(1000000/FRAMERATE-(end-start));
start =clock();
} while((c=getch())!=K_QUIT);
freechunks(level);
  delwin(gamewin); delwin(talkwin); delwin(invwin);
endwin(); return 0;}


Chunk* newchunk(void){
Chunk* new =(Chunk*)malloc(sizeof(Chunk));
new->map =(char**)malloc(sizeof(char*)*CHUNKH);
for(int i=0;i<CHUNKH;i++)
	new->map[i] =(char*)calloc(CHUNKW,1);
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

void populate(Chunk* chunk){
int n =(int)((float)CHUNKH*(float)CHUNKW*0.006);
int nb=0; do{ nb++;
int h =rand()%5;
if(h==0||h==1||h==4)	h =1;
else if(h==2)	h =2;
else if(h==3)	h =2+rand()%4;
int w =rand()%PLTFRMWMAX;
if(!(w%2)) w++;
char **platform =(char**)malloc(sizeof(char*)*(h+1));
for(int i=0;i<h+1;i++)
	platform[i] =(char*)calloc(sizeof(char*)*w,1);
platform[0][0] =1;
for(int i=0;i<w;i+=2){ platform[0][i] ='_';
	platform[0][i+1] =1;}
platform[1][0] =' ';
for(int i=1;i<w;i+=2){ platform[1][i] ='|';
		platform[1][i+1] =' ';}
if(h>=2) for(int i=0;i<w-2;i+=2)
	if(rand()%3){ platform[2][i] =' ';
		platform[2][i+1] =' ';}
if(h>=3) for(int i=0;i<w-2;i+=2)
	if(platform[2][i] && rand()%2){
		platform[3][i] =' ';
		platform[3][i+1] =' ';}
if(h>=4) for(int i=0;i<w;i++)
	if(platform[3][i] && rand()%2)
		platform[4][i] =' ';
if(h==5) for(int i=0;i<w;i++)
	if(platform[4][i] && rand()%2)
		platform[5][i] =' ';
int x, y;
int viable, tries=0; do {
	tries++;
	viable =1;
	y =rand()%CHUNKH;
	x =rand()%CHUNKW;
	if(y+h+1>=CHUNKH) viable =0;
	if(x+w>=CHUNKW) viable =0;
	if(viable) for(int i=0;i<h+1;i++) for(int j=0;j<w;j++)
		if(chunk->map[y+i][x+j]) viable =0;
} while(!viable && tries<42);
if(viable) for(int i=0;i<h+1;i++) for(int j=0;j<w;j++)
		chunk->map[y+i][x+j] =platform[i][j];
for(int i=0;i<h;i++) free(platform[i]);
free(platform);
}while(nb<n);
return;}
