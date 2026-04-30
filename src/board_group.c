#include <stdlib.h>
#include "constants.h"
#include "board.h"
#include "board_group.h"
#include "sql_driver.h"

void Boards__init(Boards* boards, const char* board_repr){
	if (!boards)
	{
		return;
	}
	for(int i = 0; i < SIZE_OF_CHARACTER_MAP; i++){
		const char repr = CHARACTER_MAP[i];
		Board* board = Board__create(repr, board_repr);
		boards->full_board[i] = board;
	}
}

Boards* Boards__create(const char* board_repr){
	Boards* result = (Boards*) malloc(sizeof(Boards));
	Boards__init(result, board_repr);
	return result;
}

void Boards__destroy(Boards** boards)
{
	if (!*boards) return;
	free(*boards);
	*boards = NULL;

}

void Boards__set_piece(Boards* boards, const char piece, const Coordinates* coordinates){
	if (!boards)
	{
		return;
	}
	const int index = piece_char_to_int(piece);
	Board* board = boards->full_board[index];
	Board__set(board, coordinates);
}

void Boards__unset_piece(Boards* boards, const char piece, const Coordinates* coordinates){
	if (!boards)
	{
		return;
	}
	const int index = piece_char_to_int(piece);
	Board* board = boards->full_board[index];
	Board__unset(board, coordinates);
}

void Boards__unset(Boards* boards, const Coordinates* coordinates){
	if (!boards)
	{
		return;
	}
	for(int i = 0; i < SIZE_OF_CHARACTER_MAP; i++)
	{	Board* board = boards->full_board[i];
		Board__unset(board, coordinates);
	}
}

char Boards__get_piece(Boards* boards, const Coordinates* coordinates){
	if (!boards)
	{
		return '\0';
	}
	for(int i = 0; i < SIZE_OF_CHARACTER_MAP; i++){
		if(Board__get(boards->full_board[i], coordinates)){
			return CHARACTER_MAP[i];
		}
	}
	return '\0';
}

bool Boards__check_piece_exists(Boards* boards, const char piece, const Coordinates* coordinates){
	if (!boards)
	{
		return false;
	}
	const int index = piece_char_to_int(piece);

	return Board__get(boards->full_board[index], coordinates);
}

Coordinates* Boards__get_coordinates_first_instance(Boards* boards, const char piece)
{
	if (!boards) return NULL;
	int index = piece_char_to_int(piece);

	Board* board = boards->full_board[index];
	return Board__get_first_instance(board);
}

CoordinateList* Boards__get_all_coordinates(Boards* boards, const char piece)
{
	if (!boards) return NULL;
	int index = piece_char_to_int(piece);

	Board* board = boards->full_board[index];
	return Board__get_all_instances(board);
}

CoordinateList* Boards__filter_out_impossible_moves(CoordinateList* moves, const char piece, const Coordinates* coordinates)
{

	return moves;
}

bool check_square_is_moveable(Boards* boards, const char piece, const Coordinates* end)
{
	char end_piece = Boards__get_piece(boards, end);
	if (end_piece)
	{
		return is_piece_white(piece) ^ is_piece_white(end_piece);
	}
	return true;
}


bool check_path_clear(Boards* boards, const char piece, const Coordinates* start, const Coordinates* end, const Coordinates* vector)
{
	Coordinates* current_coordinates = Coordinates__copy(start);

	// retrieve first nonempty coordinate if there is any
	while (Coordinates__is_equal(current_coordinates, end))
	{
		Coordinates__add(vector, current_coordinates);
		if (!Coordinates__is_equal(current_coordinates, end) && Boards__get_piece(boards, current_coordinates) != '\0') return false;
	}
	return check_square_is_moveable(boards, piece, end);
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

bool is_move_valid(Boards* boards,const char piece, const Coordinates* start, const Coordinates* end)
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
		return check_path_clear(boards, piece, start, end, vector);
	}

	// This if statement covers:
	// - Knight
	// - Paladin
	// - Dragon
	if (is_knightlike(piece))
	{
		return check_square_is_moveable(boards, piece, end);
	}
	return check_pawn_moves(boards, piece, start, end, vector);

	// TODO: STILL NEED TO ACCOUNT FOR:
	// - Castling
	// - En Passant
}