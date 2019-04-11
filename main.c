#include <stdlib.h>
#include "libtcod.h"
#include "entity.h"
#include "map.h"
#include "engine.h"



void main() {
	Engine *engine = create_engine();

	while (!TCOD_console_is_window_closed()) {
		update_engine(engine);
		render_engine(engine);
		TCOD_console_flush();
	}
}


