#include <stdlib.h>
#include <stdio.h>
#include "libtcod.h"
#include "entity.h"
#include "map.h"
#include "engine.h"



void main() {

	Engine *engine = create_engine();
	while (!engine->quit && !TCOD_console_is_window_closed()) {
		render_engine(engine);
		TCOD_console_flush();
		update_engine(engine);
	}
}


