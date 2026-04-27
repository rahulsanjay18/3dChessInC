#include <stdlib.h>
#include "constants.h"
#include "board.h"
#include "board_group.h"

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
		return '\0';
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