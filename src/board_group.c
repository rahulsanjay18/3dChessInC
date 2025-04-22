#include <stdlib.h>
#include "constants.h"
#include "board.h"
#include "board_group.h"

struct Boards{
	Board* full_board[SIZE_OF_CHARACTER_MAP];
}Boards;

void Boards__init(Boards* result, char* board_repr[BOARD_SIZE][BOARD_SIZE]){
	for(int i = 0; i < SIZE_OF_CHARACTER_MAP; i++){
		char repr = CHARACTER_MAP[i];
		Board* board = Board__create(repr, board_repr);
		resolt->full_board[i] = board;
	}
}

Boards* Boards__create(char* board_repr[BOARD_SIZE][BOARD_SIZE]){
	Boards* result = Boards* malloc(sizeof(Boards));
	Boards__init(result);
	return result;
}

void set_piece(char piece, Coordinates* coordinates){
	int index = char_to_int(piece);
	Board* board = full_board[index];
	set(board, coordinates);
}

void unset_piece(char piece, Coordinates* coordinates){
	int index = char_to_int(piece);
	Board* board = full_board[index];
	unset(board, coordinates);
}

char get_piece(Coordinates* coordinates){
	for(int i = 0; i < SIZE_OF_CHARACTER_MAP; i++){
		if(get(full_board[i], coordinates)){
			return CHARACTER_MAP[i];
		}
	}
	return '\0';
}
