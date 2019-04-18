#ifndef ENGINE_H
#define ENGINE_H

typedef struct Engine {
	Entity **entities;
	Entity *player;
	Map *map;
	bool quit;
} Engine;

Engine *create_engine();
void update_engine(Engine *engine);
void render_engine(Engine *engine);
void destroy_engine(Engine *engine);

#endif
