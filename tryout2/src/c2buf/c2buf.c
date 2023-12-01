#include "c2buf.h"

c2buf	*alloc_c2buf(int h,int w){
c2buf	*new =(c2buf*)malloc(sizeof(c2buf));
new->h =h;	new->w =w;
new->htot =h+2;	new->wtot =w+1;
int htot =new->htot, wtot =new->wtot;
new->sizetot =htot*wtot;
int sizetot =new->sizetot;
new->b =(char*)malloc(sizetot);
new->c =new->b +wtot;
new->l =(char**)malloc(htot);
char *b =new->b;
char **l =new->l;
for (int i=0; i<h; i++){
	l[i] =new->c +i*wtot;
	l[i][w] =0;}
for (int i=0; i<sizetot; i++)
	b[i] =' ';
for (int i=0; i<wtot; i++){
	b[i] =0;
	b[sizetot-wtot+i] =0;} return new;}

void	free_c2buf(c2buf* b){
free(b->l);free(b->b);
free(b);	return;}
