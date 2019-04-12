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
	//engine->entities = malloc(sizeof(Entity) * 1);
	engine->map = create_map(80, 50);

	//engine->entities[0] = engine->player;

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
		default: break;
	}
}

void render_engine(Engine *engine) {
	TCOD_console_clear(NULL);
	render_map(engine->map);
	/*for (int i = 0; i < 1; i++) {
		Entity *entity = engine->entities[i];
		TCOD_console_put_char(NULL, entity->x, entity->y, entity->ch, TCOD_BKGND_NONE);
		}
		*/
	TCOD_console_put_char(NULL, engine->player->x, engine->player->y, engine->player->ch, TCOD_BKGND_NONE);
}

