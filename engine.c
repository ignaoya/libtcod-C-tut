#include <stdlib.h>
#include "libtcod.h"
#include "entity.h"
#include "map.h"
#include "engine.h"

Engine *create_engine() {
	TCOD_console_init_root(80, 50, "These Cunning Old Depths", false, TCOD_RENDERER_SDL);
	Engine *engine;
	engine = malloc(sizeof(Engine));
	engine->player = create_entity(40, 25, '@', TCOD_white);
	engine->entities = malloc(sizeof(Entity) * 2);
	engine->map = create_map(80, 50);
	engine->quit = false;

	engine->entities[0] = engine->player;
	engine->entities[1] = create_entity(30, 25, 'G', TCOD_white);

	return engine;
}

void update_engine(Engine *engine) {
	TCOD_key_t key = TCOD_console_wait_for_keypress(true);

	switch(key.c) {
		case 'k':
			if (!isWall(engine->map, engine->player->x, engine->player->y-1))
				move(engine->player, 'u'); 
			break;
		case 'j':
			if (!isWall(engine->map, engine->player->x, engine->player->y+1))
				move(engine->player, 'd'); 
			break;
		case 'h':
			if (!isWall(engine->map, engine->player->x-1, engine->player->y))
				move(engine->player, 'l'); 
			break;
		case 'l':
			if (!isWall(engine->map, engine->player->x+1, engine->player->y))
				move(engine->player, 'r'); 
			break;
		case 'q':
			engine->quit = true;
			break;
		default: break;
	}
}

void render_engine(Engine *engine) {
	TCOD_console_clear(NULL);
	render_map(engine->map);
	for (int i = 0; i < 2; i++) {
		TCOD_console_put_char(NULL, engine->entities[i]->x, engine->entities[i]->y, engine->entities[i]->ch, TCOD_BKGND_NONE);
	}
		
}

