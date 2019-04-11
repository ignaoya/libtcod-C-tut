#include <stdlib.h>
#include "libtcod.h"
#include "map.h"	

Map * create_map(int width, int height) {

	int i, j;
	Map * map;
	map = malloc(sizeof(Map));
	map->width = width;
	map->height = height;
	map->tiles = malloc(sizeof(Tile *) * height);
	for (i = 0; i < width; i++)
		map->tiles[i] = malloc(sizeof(Tile) * width);

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			map->tiles[i][j].canWalk = true;

	setWall(map, 30, 22);
	setWall(map, 50, 22);

	return map;
}

bool isWall(Map *map, int x, int y) {
	return !map->tiles[y][x].canWalk;
}

void setWall(Map *map, int x, int y) {
	map->tiles[y][x].canWalk = false;
}

void render_map(Map *map) {
	TCOD_color_t darkWall = {0, 0, 100};
	TCOD_color_t darkGround = {50, 50, 150};

	for (int x=0; x < map->width; x++) {
		for (int y=0; y < map->height; y++) {
			TCOD_console_set_char_background(NULL, x, y, isWall(map, x, y) ? darkWall : darkGround, TCOD_BKGND_SET );
		}
	}
}

