#ifndef GAME
#define GAME
#include "coordinates.h"
#include "game_state.h"

typedef struct Game{
    GameState game_state;
    Coordinates* start_move;
    Coordinates* end_move;

} Game;

void initialize_game();
Game* Game__create();
bool Game__move(Game* game, Coordinates* start, Coordinates* end);
void Game__loop(Game* game);
void Game__save(Game* game, char* filepath);
#endif
