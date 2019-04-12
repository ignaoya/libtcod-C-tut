#include "stdlib.h"
#include "entity.h"


Entity *create_entity(int x, int y, int ch, TCOD_color_t color) {
	Entity *entity;
	entity = malloc(sizeof(Entity));
	entity->x = x;
	entity->y = y;
	entity->ch = ch;
	entity->color = color;

	return entity;
}

void move(Entity * entity, int direction) {
	switch(direction) {
		case 'u': entity->y--; break;
		case 'd': entity->y++; break;
		case 'l': entity->x--; break;
		case 'r': entity->x++; break;
		default: break;
	}
}

