#include "whispers.h"

void	getoffsets(vect pos, size map, vect *m_o, vect *p_a, vect *m_c){
vect	map_offset; //in the map buffer
vect	print_area; //  "   offsets
vect	map_corner; //on the screen
if (pos.y > LINES/2){		//player being centered
	map_offset.y = pos.y-LINES/2; //this means
	map_corner.y = 0;}	//the map exceeds the screen
else {	map_offset.y = 0;	//towards the top or left
	map_corner.y = LINES/2-pos.y;}
if (pos.x > COLS/2){
	map_offset.x = pos.x-COLS/2;
	map_corner.x = 0;}
else {	map_offset.x = 0;
	map_corner.x = COLS/2-pos.x;}
//how much can we print without exceeding bottom/right boundaries
if (map.h-map_offset.y > LINES-map_corner.y)
	print_area.y = LINES-map_corner.y;
else print_area.y = map.h-map_offset.y;
if (map.w-map_offset.x > COLS-map_corner.x)
	print_area.x = COLS-map_corner.x;
else print_area.x = map.w-map_offset.x;
*m_o = map_offset;
*p_a = print_area;
*m_c = map_corner; return;}

void	drawmap(vect pos, ROOM *map){
vect	map_offset, print_area, map_corner;
getoffsets(pos, (size){map->h,map->w}, &map_offset, &print_area, &map_corner);
for (int i=0; i<print_area.y; i++)
	mvaddnstr(map_corner.y+i, map_corner.x,
		map->map[i+map_offset.y]+map_offset.x, print_area.x);
refresh(); return;}

void	erasemap(vect pos, ROOM *map){
vect	map_offset, print_area, map_corner;
getoffsets(pos, (size){map->h,map->w}, &map_offset, &print_area, &map_corner);
for (int i=0; i<print_area.y; i++)
	space(map_corner.y+i,map_corner.x, print_area.x);
refresh(); return;}
