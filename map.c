#include <stdlib.h>
#include "libtcod.h"
#include "map.h"	

Map * create_map() {

	int i, j;
	Map * map;
	map = malloc(sizeof(Map));
	map->width = 80;
	map->height = 45;
	map->tiles = malloc(map->height * sizeof(Tile *) * (map->width * sizeof(Tile )));
	for (i = 0; i < map->width; i++)
		map->tiles[i] = malloc(map->width * sizeof(Tile));

	for (i = 0; i < map->height; i++)
		for (j = 0; j < map->width; j++)
			map->tiles[i][j] = create_tile();

	setWall(map, 30, 22);
	setWall(map, 50, 22);

	return map;
}

Tile create_tile() {
	Tile tile;
	tile.canWalk = true;

	return tile;
}

bool isWall(Map *map, int x, int y) {
	return !map->tiles[y][x].canWalk;
}

void setWall(Map *map, int x, int y) {
	map->tiles[y][x].canWalk = false;
}

void render_map(Map *map) {
	TCOD_color_t darkWall = {0, 0, 100};
	TCOD_color_t darkGround = {50, 30, 150};

	for (int x=0; x < map->width; x++) {
		for (int y=0; y < map->height; y++) {
			TCOD_console_set_char_background(NULL, x, y, isWall(map, x, y) ? darkWall : darkGround, TCOD_BKGND_SET );
		}
	}
}

void destroy_map(Map *map) {
	for (int i = 0; i < map->width; i++)
		free(map->tiles[i]);
	free(map->tiles);
	free(map);
}
 
