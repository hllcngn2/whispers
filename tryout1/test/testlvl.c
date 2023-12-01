#include <ncurses.h>
#include <stdlib.h> //malloc()

#include "vector.h"

#define LVL_HEIGHT 30
#define LVL_WIDTH 90
#define SCREEN_WIDTH 45
#define START_POS_I 17
#define START_POS_Y 6

int	main(int ac, char **av){

FILE *f;
char **m;
vector	ppos;
char	playing;

//ncurses init
initscr();

//allocation
m=(char **)malloc(sizeof(char *)*LVL_HEIGHT);
for(char i=0; i<LVL_HEIGHT; i++) m[i]=(char *)malloc(LVL_WIDTH);

//initialization
playing = 1;
ppos.i=16;
ppos.j=7;

//loading lvl
f=fopen("lvl/testlvl", "r");
//for(char i=0; i<LVL_HEIGHT*LVL_WIDTH; i++) m[i/LVL_WIDTH][i%LVL_WIDTH]=fgetc(f);
for(char i=0; i<LVL_HEIGHT; i++){ for(char j=0; j<LVL_WIDTH; j++){
m[i][j]=fgetc(f);} fgetc(f);}
fclose(f);

while(playing){

//display
//lvl
move(0, 0);
for(char i=0; i<LVL_HEIGHT; i++){
for(char j=0; j<SCREEN_WIDTH; j++){
addch(' '); addch(m[i][j]);}
addch('\n');}
//character
mvaddch(ppos.i, ppos.j*2-1, '@');

switch(getch()){
	case 'q':
		playing = 0;
		break;
	case 'a':
		if(ppos.j>1) ppos.j--;
		break;
	case 'd':
		if(ppos.j<SCREEN_WIDTH) ppos.j++;
		break;
}

}

endwin();
return 0;}
