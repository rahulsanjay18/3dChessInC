#pragma once

#include "constants.h"
#include "coordinates.h"
#include "board.h"
#ifndef BOARDS
#define BOARDS

typedef struct Boards{
    Board* full_board[SIZE_OF_CHARACTER_MAP];
} Boards;

Boards* Boards__create(char* board_repr[BOARD_SIZE][BOARD_SIZE]);
void Boards__set_piece(Boards* boards, char piece, const Coordinates* coordinates);
void Boards__unset_piece(Boards* boards, char piece, const Coordinates* coordinates);
char Boards__get_piece(Boards* boards, const Coordinates* coordinates);
#endif
