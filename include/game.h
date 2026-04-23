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
Game* Game__create(char* filepath, bool isTesting);
bool Game__move(Game* game, Coordinates* start, Coordinates* end);
bool Game__move_with_piece(const Game* game, char piece, const Coordinates* start, const Coordinates* end);
void Game__loop(Game* game);
#endif
