#ifndef ENTITY_H
#define ENTITY_H

#include "libtcod.h"

typedef struct Entity {
	int x;
	int y;
	int c;
} Entity;

void move(Entity * entity, int direction);

#endif
