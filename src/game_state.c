#include <stdlib.h>
#include <stdbool.h>
#include "constants.h"
#include "board_group.h"
#include "game_state.h"

void GameState__init(GameState* game_state, char* board_repr[BOARD_SIZE][BOARD_SIZE], bool is_white_turn, const bool castle_status[CASTLES], const bool is_checkmate){
	if (!game_state)
	{
		return;
	}
	game_state->boards = Boards__create(board_repr);
	game_state->is_white_turn = is_white_turn;
	*(game_state->castle_status) = castle_status;
	game_state->is_checkmate = is_checkmate;
}
GameState* GameState__create(char* board_repr[BOARD_SIZE][BOARD_SIZE], bool is_white_turn, bool castle_status[CASTLES], bool is_checkmate){
	GameState* result = (GameState*) malloc(sizeof(GameState));
	
	GameState__init(result, board_repr, is_white_turn, castle_status, is_checkmate);
	return result;
}
void make_move(GameState* game_state, const Coordinates* start, Coordinates* end){
	if (!game_state)
	{
		return;
	}
	Boards* boards = game_state->boards;
	char piece = Boards__get_piece(boards, start);
	Boards__set_piece(boards, piece, start);
}
int get_piece_num(GameState* game_state, Coordinates* location)
{
	return 0;
}
char get_piece_char(GameState* game_state, Coordinates* location)
{
	return '\0';
}
