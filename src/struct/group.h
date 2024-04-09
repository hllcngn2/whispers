#ifndef GROUP_H
#define GROUP_H

#include "vector.h"

typedef struct cell {
	char i;
	char j;
	struct cell *next;
} cell;

typedef struct group {
	char weight;
	vector c;
	cell *list;
	struct group *next;
} group;

typedef struct path {
	group *g;
	cell *a;
	group *h;
	cell *b;
	struct path *next;
} path;

#endif
