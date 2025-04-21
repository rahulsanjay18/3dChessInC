#include <stdint.h>
#include <stdbool.h>
#include "coordinates.h"
#ifndef BOARD
#define BOARD
/******************************
 * MODULE DEFINITION:
 * This is the board module, a simple struct and associated functions that
 * defines a bitboard that is supposed to represent the location of a given
 * piece. If the bit in the bitboard is set to high, that means the piece
 * that the bitboard is representing is in that location.
 *
 * All functions in this interfact simply deal with manipulating the bits 
 * in the bitboard.
 */


typedef struct Board Board;

Board* Board__create();

/*
 * Given the board and coordinates, set the bit at the location (x,y,z) to 1.
 *
 * Note that the x direction in the board is noted by the index of each array,
 * the y direction is every group of 8 in the uint64 int the array, and the z 
 * is the individual bit in each group of 8.
 */
void set(Board* self, Coordinates* location);

/*
 * Given the board and the coordinates, set the bit at the location (x, y, z) to 0.
 */
void unset(Board* self, Coordinates* location);

/*
 * Return the value at thhe given position on the board.
 */
bool get(Board* self, Coordinates* location);
#endif
