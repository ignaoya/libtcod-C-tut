#include "entity.h"


void move(Entity * entity, int direction) {
	switch(direction) {
		case 'u': entity->y--; break;
		case 'd': entity->y++; break;
		case 'l': entity->x--; break;
		case 'r': entity->x++; break;
		default: break;
	}
}
