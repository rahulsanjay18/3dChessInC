#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "constants.h"
#include "coordinates.h"
#include "board.h"


/*
 * The following two functions are used to make it easier
 * to set and get bits. The general formula for getting the
 * right bit in a 64 bit variable is:
 * `1 << BOARD_SIZE * y + z;`
 * so if you want to set it, you | it with the integer, if you
 * want to unset it, you & it with its complement, and if you just
 * want the value, you & it and then shift it down by the bit shift
 * value (BOARD_SIZE ...)
 * These functions make that easier.
 */
uint64_t get_bit_shifted_value(unsigned int y, unsigned int z){
	return BOARD_SIZE * y + z;
}

uint64_t get_yz_integer(unsigned int y, unsigned int z){
	return 1 << get_bit_shifted_value(y, z);
}

void Board__init(Board* board, char repr, char* board_repr[BOARD_SIZE][BOARD_SIZE]){
	if (!board)
	{
		return;
	}
	board->representing_character = repr;
	for(int x = 0; x < BOARD_SIZE; x++){
		for(int y = 0; y < BOARD_SIZE; y++){
			for(int z = 0; z < BOARD_SIZE; z++){
				if(board_repr[x][y][z] == repr){
					Coordinates* coordinates = Coordinates__create(x, y, z);
					Board__set(board, coordinates);
					Coordinates__destroy(coordinates);
				}
			}
		}
	}
}

Board* Board__create(const char repr, char* board_repr[BOARD_SIZE][BOARD_SIZE]){
	Board* board = (Board*) malloc(sizeof(Board));
	Board__init(board, repr, board_repr);
	return board;
}

void Board__set(Board* self, const Coordinates* location){
	// Note that the array index goes in the x direction.
	uint64_t plane = (self->bitboard[location->x]);
	plane |= get_yz_integer(location->y, location->z);
	self->bitboard[location->x] = plane;
}

void Board__unset(Board* self, const Coordinates* location){
	uint64_t plane = (self->bitboard[location->x]);
	plane &= !(get_yz_integer(location->y, location->z));
	self->bitboard[location->x] = plane;
}

bool Board__get(Board* self, const Coordinates* location){
	if (!self)
	{
		return NULL;
	}
	unsigned int y = location->y;
	unsigned int z = location->z;
	return (bool)((self->bitboard[location->x] & get_yz_integer(y, z)) >> get_bit_shifted_value(y, z));
}
