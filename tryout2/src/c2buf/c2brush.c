#include "c2buf.h"

void fill_c2(c2buf *buf, int y,int x,int h,int w, char c){
for (int i=0; i<h; i++) stroke_c2(buf, y+i,x, w, c); return;}

void box_c2(c2buf *buf){
vline_c2(buf, 0); vline_c2(buf, buf->w-1);
line_c2(buf, 0); line_c2(buf, buf->h-1); return;}

void line_c2(c2buf *buf, int y){
stroke_c2(buf, y,0, buf->w, '-'); return;}
void vline_c2(c2buf *buf, int x){
vstroke_c2(buf, 0,x, buf->h, '|'); return;}

void stroke_c2(c2buf *buf, int y,int x, int n, char c){
char *p =buf->l[y]+x; //todo: stroke() over multiple lines
if (n >0) for (int i=0; i<n && p[i]; i++){ p[i] =c;}
else	  for (int i=0; i>n && p[i]; i--){ p[i] =c;} return;}
void vstroke_c2(c2buf *buf, int y,int x, int n, char c){
char **l =buf->l +y*sizeof(char*);
if (n >0) for (int i=0; i<n && l[i][x]; i++){ l[i][x] =c;}
else	  for (int i=0; i>n && l[i][x]; i--){ l[i][x] =c;} return;}

void stroketil_c2(c2buf *buf, int y,int x, int n, char c, char X){
char *p =buf->l[y]+x;
if (n >0) for (int i=0; i<n && p[i] && p[i]!=X; i++){ p[i] =c;}
else	  for (int i=0; i>n && p[i] && p[i]!=X; i--){ p[i] =c;} return;}
void vstroketil_c2(c2buf *buf, int y,int x, int n, char c, char X){
char **l =buf->l +y*sizeof(char*);
if (n >0) for (int i=0; i<n &&l[i][x]; &&l[i][x]!=X; i++){ l[i][x]=c;}
else	  for (int i=0; i>n &&l[i][x]; &&l[i][x]!=X; i--){ l[i][x]=c;} return;}
