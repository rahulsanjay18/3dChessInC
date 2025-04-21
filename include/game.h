#include "coordinates.h"
#include "game_state.h"
#ifndef GAME
#define GAME
typedef struct Game Game;

void initialize_game();
bool move(Coordinates* start, Coordinates* end);
void game_loop();
#endif
