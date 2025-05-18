#include <stdlib.h>
#include "constants.h"
#include "board.h"
#include "board_group.h"

struct Boards{
	Board* full_board[SIZE_OF_CHARACTER_MAP];
};

void Boards__init(Boards* result, char* board_repr[BOARD_SIZE][BOARD_SIZE]){
	for(int i = 0; i < SIZE_OF_CHARACTER_MAP; i++){
		char repr = CHARACTER_MAP[i];
		Board* board = Board__create(repr, board_repr);
		result->full_board[i] = board;
	}
}

Boards* Boards__create(char* board_repr[BOARD_SIZE][BOARD_SIZE]){
	Boards* result = (Boards*) malloc(sizeof(Boards));
	Boards__init(result, board_repr);
	return result;
}

void Boards__set_piece(Boards* boards, char piece, Coordinates* coordinates){
	int index = char_to_int(piece);
	Board* board = boards->full_board[index];
	Board__set(board, coordinates);
}

void Boards__unset_piece(Boards* boards, char piece, Coordinates* coordinates){
	int index = char_to_int(piece);
	Board* board = boards->full_board[index];
	Board__unset(board, coordinates);
}

char Boards__get_piece(Boards* boards, Coordinates* coordinates){
	for(int i = 0; i < SIZE_OF_CHARACTER_MAP; i++){
		if(Board__get(boards->full_board[i], coordinates)){
			return CHARACTER_MAP[i];
		}
	}
	return '\0';
}
