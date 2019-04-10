#ifndef ENTITY_H
#define ENTITY_H

#include "libtcod.h"

typedef struct Entity {
	int x;
	int y;
	int c;
	TCOD_color_t color;
} Entity;

void move(Entity * entity, int direction);

#endif
