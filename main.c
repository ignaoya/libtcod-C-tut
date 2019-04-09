#include <stdlib.h>
#include "libtcod.h"

typedef struct Entity {
	int x;
	int y;
	int c;
} Entity;

void handle_input(Entity * entity, TCOD_key_t key);
void move(Entity * entity, int direction);

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
		handle_input(player, key);
	}
}

void handle_input(Entity * entity, TCOD_key_t key) {
	switch(key.c) {
		case 'k': move(entity, 'u'); break;
		case 'j': move(entity, 'd'); break;
		case 'h': move(entity, 'l'); break;
		case 'l': move(entity, 'r'); break;
		default: break;
	}
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
