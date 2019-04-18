#ifndef MAP_H
#define MAP_H

#include "libtcod.h"

typedef struct Tile {
	bool canWalk;
} Tile;

typedef struct Map {
	int width, height;
	Tile **tiles;
} Map;

Map *create_map();
Tile create_tile();
bool isWall(Map *map, int x, int y);
void setWall(Map *map, int x, int y);
void render_map(Map *map);
void destroy_map(Map *map);

#endif
