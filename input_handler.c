#include "input_handler.h"

void handle_input(Entity * entity, TCOD_key_t key) {
	switch(key.c) {
		case 'k': move(entity, 'u'); break;
		case 'j': move(entity, 'd'); break;
		case 'h': move(entity, 'l'); break;
		case 'l': move(entity, 'r'); break;
		default: break;
	}
}
