#include "whispers.h"

#define LVH 100
#define LVW 300
#define STRTPOSY 28
#define STRTPOSX 150

STATIC_LVL *gen_static_lvl();
void disp_static_lvl(STATIC_LVL*,vect, WINDOW*,int,int);
void free_static_lvl(STATIC_LVL*);



int	main(int ac, char **av){
initscr(); cbreak();
noecho(); curs_set(0);
refresh();

WINDOW	*wg =newwin(WGH,WGW,1,2);
wborder(wg,'|','|','-','-', '-','-','-','-');

STATIC_LVL	*slvl =gen_static_lvl();

//vect	pos =(vect){STRTPOSY,STRTPOSX};
vect pos =(vect){70,150};

char	c =0;
do {
switch(c){
case K_LEFT: pos.x--; break;
case K_RIGHT: pos.x++; break;
case K_JUMP: pos.y-=2; break;
default: break;}

disp_static_lvl(slvl,pos, wg,1,1);
mvwaddch(wg, WGH/2,WGW/2, '@');
wrefresh(wg);

} while ((c=getch()) !='0');
free_static_lvl(slvl);
delwin(wg);
endwin(); return 0;}



STATIC_LVL *gen_static_lvl(){
STATIC_LVL *new =(STATIC_LVL*)malloc(sizeof(STATIC_LVL));
new->h =LVH; new->w =LVW;
new->map =alloc_c2buf(new->h,new->w);

line_c2(new->map, 30);
vline_c2(new->map, 105);
vline_c2(new->map, 115);
return new;}

void disp_static_lvl(STATIC_LVL *slvl,vect pos, WINDOW *win,int y,int x){
c2buf	*buf =slvl->map;
char	*p =buf->l[pos.y-WGH/2]+pos.x-WGW/2;
for (int i=0; i<WGH-y*2; i++){
	mvwaddnstr(win,y+i,x, p,WGW-x*2);
	p +=buf->wtot;}
	//p =(buf->l[pos.y-WGH/2+i])+pos.x-WGW/2;
return;}

void free_static_lvl(STATIC_LVL *slvl){
free_c2buf(slvl->map);
free(slvl); return;}
