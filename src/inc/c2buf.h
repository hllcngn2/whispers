#pragma once

#include <stdlib.h>

typedef struct{
	int	htot,wtot, h,w, sizetot;
	char	*b,*c;
	char	**l;
} c2buf;

//c2buf.c
c2buf	*alloc_c2buf(int,int);
void	free_c2buf(c2buf*);

//c2brush.c
void fill_c2(c2buf *buf, int y,int x,int h,int w, char c);
void box_c2(c2buf*);
void line_c2(c2buf *buf, int y);
void vline_c2(c2buf *buf, int x);
void stroke_c2(c2buf*, int,int, int, char);
void vstroke_c2(c2buf*, int,int, int, char);
void stroketil_c2(c2buf *buf, int y,int x, int n, char c, char X);
void vstroketil_c2(c2buf *buf, int y,int x, int n, char c, char X);
