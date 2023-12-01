#pragma once

#include "c2buf.h"

typedef struct{
	int	y,x;
} vect;


typedef struct{
	int	h,w;
	c2buf	*map;
} STATIC_LVL;
