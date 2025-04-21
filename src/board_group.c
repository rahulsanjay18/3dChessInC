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
		Board__create(repr, board_repr);
	}
}

Boards* Boards__create(char* board_repr[BOARD_SIZE][BOARD_SIZE]){
	Boards* result = Boards* malloc(sizeof(Boards));
	Boards__init(result);
	return result;
}
