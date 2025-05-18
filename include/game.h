#include "coordinates.h"
#include "game_state.h"
#ifndef GAME
#define GAME
typedef struct Game Game;

void initialize_game();
Game* Game__create();
bool Game__move(Game* game, Coordinates* start, Coordinates* end);
void Game__loop(Game* game);
void Game__save(Game* game, char* filepath);
#endif
