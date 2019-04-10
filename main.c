#include <stdlib.h>
#include "libtcod.h"
#include "input_handler.h"


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


