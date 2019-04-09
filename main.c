#include <stdlib.h>
#include "libtcod.h"

typedef struct Entity {
	int x;
	int y;
	int c;
} Entity;

void move(Entity * entity, TCOD_key_t);

void main() {
	TCOD_console_init_root(80, 50, "These Cunning Old Depths", false, TCOD_RENDERER_SDL);

	Entity * player;
	player = malloc(sizeof(Entity));
	player->x = 40;
	player->y = 25;
	player->c = '@';

	while (!TCOD_console_is_window_closed()) {
		TCOD_console_clear(NULL);
		TCOD_console_put_char(NULL, player->x, player->y, player->c, TCOD_BKGND_NONE);
		TCOD_console_flush();
		TCOD_key_t key = TCOD_console_wait_for_keypress(true);
		move(player, key);
	}
}

void move(Entity * entity, TCOD_key_t key) {
	switch(key.c) {
		case 'k': entity->y--; break;
		case 'j': entity->y++; break;
		case 'h': entity->x--; break;
		case 'l': entity->x++; break;
		default: break;
	}
}
