#ifndef GAME_STATE
#define GAME_STATE
#include <stdbool.h>
#include "constants.h"
#include "board_group.h"
#include "coordinates.h"

struct Boards;

typedef struct GameState{
	Boards* boards;
	CoordinateList* check_list;
	int* captured_pieces;
	bool is_white_turn;
	bool castle_status[CASTLES];
	bool is_checkmate;
	bool is_check;
}GameState;

GameState* GameState__create(const char* board_repr,int* captured_pieces,bool is_white_turn, const bool castle_status[CASTLES], bool is_checkmate, bool is_check, bool isTesting);
bool make_move_with_coords(GameState* game_state, const Coordinates* start, const Coordinates* end);
bool make_move_with_piece(const GameState* game_state, char piece, const Coordinates* start, const Coordinates* end);
char get_piece_char(const GameState* game_state, const Coordinates* location);
#endif
