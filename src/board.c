#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "constants.h"
#include "coordinates.h"
#include "board.h"

const int X_DIM_OFFSET = BOARD_SIZE * BOARD_SIZE;
const int Y_DIM_OFFSET = BOARD_SIZE;
const uint64_t ONE = 1;
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
	return ONE << get_bit_shifted_value(y, z);
}

uint64_t get_offset(const int x, const int y, const int z)
{
	return x * X_DIM_OFFSET + y * Y_DIM_OFFSET + z;
}

void Board__init(Board* board, const char repr, const char* board_repr){
	if (!board)
	{
		return;
	}
	board->representing_character = repr;
	for(int x = 0; x < BOARD_SIZE; x++){
		board->bitboard[x] = 0;
		for(int y = 0; y < BOARD_SIZE; y++){
			for(int z = 0; z < BOARD_SIZE; z++){
				uint64_t offset = get_offset(x, y, z);
				if(board_repr[offset] == repr){
					Coordinates* coordinates = Coordinates__create(x, y, z);
					Board__set(board, coordinates);
					Coordinates__destroy(&coordinates);
				}

			}
		}
	}
}

Board* Board__create(const char repr, const char* board_repr){
	Board* board = (Board*) malloc(sizeof(Board));
	Board__init(board, repr, board_repr);
	return board;
}

void Board__destroy(Board** board)
{
	if (!*board) return;
	free(*board);
	*board = NULL;

}

void Board__set(Board* self, const Coordinates* location){
	// Note that the array index goes in the x direction.
	uint64_t plane = (self->bitboard[location->x]);
	uint64_t val = get_yz_integer(location->y, location->z);
	plane |=val;
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
