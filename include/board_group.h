#include "constants.h"
#include "coordinates.h"
#include "board.h"
#ifndef BOARDS
#define BOARDS
struct Boards;

Boards* Boards__create(char* board_repr[BOARD_SIZE][BOARD_SIZE]);
void set_piece(char piece, Coordinates* coordinates);
void unset_piece(char piece, Coordinates* coordinates);
char get_piece(Coordinates* coordinates);
#endif
