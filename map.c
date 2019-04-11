#include "libtcod.h"
#include "Map.h"	

Map * create_map(int width, int height) {

	int i, j;
	Map * map;
	map = malloc(sizeof(Map));
	a->width = width;
	a->height = height;
	a->tiles = malloc(sizeof(Tile *) * height);
	for (i = 0; i < width; i++)
		a->tiles[i] = malloc(sizeof(Tile) * width);

	for (i = 0; i < height; i++)
		for (j = 0; < width; j++)
			a->tiles[i][j] = true;

	setWall(map, 30, 22);
	setWall(map, 50, 22);
}

bool isWall(Map map, int x, int y) {
	return !map->tiles[y][x].canWalk;
}

void setWall(Map map, int x, int y) {
	map->tiles[y][x].canWalk = false;
}

void render_map(Map map) {
	TCOD_color_t darkWall = {0, 0, 100};
	TCOD_color_t darkGround = {50, 50, 150};

	for (int x=0; x < width; x++) {
		for (int y=0; y < height; y++) {
			TCOD_console_set_char_background(x, y, isWall(map, x, y) ? darkWall : darkGround );
		}
	}
}

