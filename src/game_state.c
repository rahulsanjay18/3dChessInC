#include <stdlib.h>
#include <stdbool.h>
#include "constants.h"
#include "board_group.h"
#include "game_state.h"
#include "sql_driver.h"

void GameState__init(GameState* game_state, const char* board_repr, bool is_white_turn, const bool castle_status[CASTLES], const bool is_checkmate, const bool is_check, bool isTesting){
	if (!game_state)
	{
		return;
	}
	open_db(isTesting);
	game_state->boards = Boards__create(board_repr);
	game_state->is_white_turn = is_white_turn;
	*(game_state->castle_status) = castle_status;
	game_state->is_check = is_check;
	game_state->is_checkmate = is_checkmate;
}
GameState* GameState__create(const char* board_repr, bool is_white_turn, const bool castle_status[CASTLES], bool is_checkmate, bool is_check, bool isTesting)
{
	GameState* result = (GameState*) malloc(sizeof(GameState));
	
	GameState__init(result, board_repr, is_white_turn, castle_status, is_checkmate, is_check, isTesting);
	return result;
}

bool make_move(Boards* boards, const char piece, const Coordinates* start, const Coordinates* end)
{

	bool is_valid = is_move_valid(piece, start, end);
	if (!is_valid) return false;

	Boards__unset_piece(boards, piece, start);
	Boards__set_piece(boards, piece, end);

	return true;
}

bool make_move_with_coords(GameState* game_state, const Coordinates* start, const Coordinates* end){
	if (!game_state)
	{
		return false;
	}
	Boards* boards = game_state->boards;
	char piece = Boards__get_piece(boards, start);
	if (piece == '\0') return false;

	return make_move(boards, piece, start, end);
}

bool make_move_with_piece(const GameState* game_state, const char piece, const Coordinates* start, const Coordinates* end)
{
	Boards* boards = game_state->boards;
	bool does_piece_exist = Boards__check_piece_exists(boards, piece, start);
	if (!does_piece_exist) return false;

	return make_move(boards, piece, start, end);
}

char get_piece_char(const GameState* game_state, const Coordinates* location)
{
	const char piece = Boards__get_piece(game_state->boards, location);
	return piece;
}
