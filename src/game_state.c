#include <stdlib.h>
#include <stdbool.h>
#include "constants.h"
#include "board_group.h"
#include "game_state.h"
#include "sql_driver.h"

void GameState__init(GameState* game_state, const char* board_repr, int* captured_pieces, bool is_white_turn, const bool castle_status[CASTLES], const bool is_checkmate, const bool is_check, bool isTesting){
	if (!game_state)
	{
		return;
	}
	open_db(isTesting);
	game_state->boards = Boards__create(board_repr);
	game_state->check_list = NULL;
	game_state->captured_pieces = captured_pieces;
	game_state->is_white_turn = is_white_turn;
	*(game_state->castle_status) = castle_status;
	game_state->is_check = is_check;
	game_state->is_checkmate = is_checkmate;
}
GameState* GameState__create(const char* board_repr, int* captured_pieces, bool is_white_turn, const bool castle_status[CASTLES], bool is_checkmate, bool is_check, bool isTesting)
{
	GameState* result = (GameState*) malloc(sizeof(GameState));
	
	GameState__init(result, board_repr, captured_pieces, is_white_turn, castle_status, is_checkmate, is_check, isTesting);
	return result;
}

bool make_move(Boards* boards, const char piece, const Coordinates* start, const Coordinates* end)
{

	// if in check, see if moves are in the check list
	bool is_valid = is_move_possible(piece, start, end);
	if (!is_valid) return false;
	// check if move creates a check on its own king
	Boards__unset_piece(boards, piece, start);
	Boards__set_piece(boards, piece, end);
	// check if in check or mate
	return true;
}

bool make_move_with_coords(GameState* game_state, const Coordinates* start, const Coordinates* end){
	if (!game_state)
	{
		return false;
	}
	Boards* boards = game_state->boards;
	const char piece = Boards__get_piece(boards, start);
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
	return Boards__get_piece(game_state->boards, location);;
}

// void is_board_in_check_or_mate(const GameState* game_state, char piece, const Coordinates* start, const Coordinates* end)
// {
// 	// get valid moves for the piece that moved
// 	CoordinateList* piece_move_list = get_possible_moves(piece, end);
//
// 	char opposite_king = game_state->is_white_turn ? BLACK_KING : WHITE_KING;
// 	Coordinates* king_coordinates = Boards__get_coordinates_first_instance(game_state->boards, opposite_king);
// 	// TODO: note that get coordinates returns all hypothetical moves, not accounting for pieces blocking the moves.
// 	CoordinateList* king_moves = get_possible_moves(piece, king_coordinates);
//
// 	// check if straight pieces have discovered check
// 	// this is done by finding the locations of all existing straight pieces,
// 	// then do is_move_valid(piece, loc, start) && is_move_valid(piece, loc, opp_king_loc)
// 	// then check for if opposite pieces can get in the way
// 	// store possible moves in list
// 	// if all false, return false
// 	// if true, check for mate
// 	// get all opposite king moves
// 	// see if pieces intersect with that
// }

bool check_square_is_moveable(Boards* boards, const char piece, const Coordinates* end)
{
	char end_piece = Boards__get_piece(boards, end);
	if (end_piece)
	{
		return is_piece_white(piece) ^ is_piece_white(end_piece);
	}
	return true;
}


bool check_path_clear(const GameState* game_state, const char piece, const Coordinates* start, const Coordinates* end, const Coordinates* vector)
{
	Coordinates* current_coordinates = Coordinates__copy(start);

	// retrieve first nonempty coordinate if there is any
	while (Coordinates__is_equal(current_coordinates, end))
	{
		Coordinates__add(vector, current_coordinates);
		if (!Coordinates__is_equal(current_coordinates, end) && Boards__get_piece(game_state->boards, current_coordinates) != '\0') return false;
	}
	return check_square_is_moveable(game_state->boards, piece, end);
}

bool check_pawn_moves(Boards* boards, const char piece, const Coordinates* start, const Coordinates* diff, const Coordinates* end)
{

	// No attack pawn
	if (diff->x != 0 && diff->y == 0 && diff-> z == 0)
	{
		const int adder = (piece == WHITE_PAWN) ? 1 : -1;
		Coordinates* forward_move = Coordinates__copy(start);
		forward_move->x = start->x + adder;
		const char intermediary_piece = Boards__get_piece(boards, forward_move);

		// checks for special pawn first move
		if ((piece == WHITE_PAWN && start->x == 1 && diff->x == 2) || (piece==BLACK_PAWN && start->x == 6 && diff->x == -2))
		{
			forward_move->x = start->x + adder;
			const char end_piece = Boards__get_piece(boards, forward_move);
			return intermediary_piece == '\0' && end_piece == '\0';

		}

		return intermediary_piece == '\0';

	}

	return check_square_is_moveable(boards, piece, end);
}

bool is_move_valid(const GameState* game_state,const char piece, const Coordinates* start, const Coordinates* end)
{
	if (Coordinates__is_equal(start, end)) return false;
	bool is_possible = is_move_possible(piece, start, end);
	if (!is_possible) return false;

	Coordinates* diff = Coordinates__subtract(start, end);
	Coordinates* vector = NULL;
	// the next block covers:
	// - Rook
	// - Priest
	// - Bishop
	// - Queen
	// - King
	// - General
	// - Wizard
	// - Duke
	if (is_face_piece(piece))
	{
		vector = get_rook_vector_index(diff);
	}
	if (!vector && is_edge_piece(piece))
	{
		vector = get_priest_vector_index(diff);
	}
	if (!vector && is_vertex_piece(piece))
	{
		vector = get_bishop_vector_index(diff);
	}
	if (vector)
	{
		return check_path_clear(game_state, piece, start, end, vector);
	}

	//This if statement covers:
	// - Knight
	// - Paladin
	// - Dragon
	if (is_knightlike(piece))
	{
		return check_square_is_moveable(game_state->boards, piece, end);
	}
	return check_pawn_moves(game_state->boards, piece, start, end, vector);
}