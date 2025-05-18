#include "constants.h"
#include "coordinates.h"
#include "board.h"
#ifndef BOARDS
#define BOARDS
typedef struct Boards Boards;

Boards* Boards__create(char* board_repr[BOARD_SIZE][BOARD_SIZE]);
void Boards__set_piece(Boards* boards, char piece, Coordinates* coordinates);
void Boards__unset_piece(Boards* boards, char piece, Coordinates* coordinates);
char Boards__get_piece(Boards* boards, Coordinates* coordinates);
#endif
