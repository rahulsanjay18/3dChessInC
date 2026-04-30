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
	/*
	 * Initializes the board struct.
	 *
	 * Args:
	 *	board: The board struct to initialize.
	 *	repr: The piece (represented by a character) that this bitboard represents the locations of
	 *	board_repr: The board representation of all pieces on the overall board.
	 */
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
	/*
	 * create a bitboard.
	 *
	 * Args:
	 *	repr: the piece this character represents.
	 *	board_repr: A BOARD_SIZE x BOARD_SIZE x BOARD_SIZE array where each
	 *	entry represents the piece on the board at that location. The bitboard
	 *	constructed is only of the piece that repr is supposed to represent.
	 *
	 * Returns:
	 *	Board pointer pointing to the bitboard.
	 */
	Board* board = (Board*) malloc(sizeof(Board));
	Board__init(board, repr, board_repr);
	return board;
}

void Board__destroy(Board** board)
{
	/*
	 * Delete board and its contents.
	 *
	 * Args:
	 *	board: board to delete.
	 */
	if (!*board) return;
	free(*board);
	*board = NULL;

}

void Board__set(Board* self, const Coordinates* location){
	/*
	 * Set the location on the board to one.
	 *
	 * Args:
	 *	self: The board whose bit the function will set to one.
	 *	location: The location that will be set to one.
	 */
	// Note that the array index goes in the x direction.
	uint64_t plane = (self->bitboard[location->x]);
	uint64_t val = get_yz_integer(location->y, location->z);
	plane |=val;
	self->bitboard[location->x] = plane;
}

void Board__unset(Board* self, const Coordinates* location){
	/*
	 * Set the location on the board to zero.
	 *
	 * Args:
	 *	self: The board whose bit the function will set to zero.
	 *	location: The location that will be set to zero.
	 */
	uint64_t plane = (self->bitboard[location->x]);
	plane &= !(get_yz_integer(location->y, location->z));
	self->bitboard[location->x] = plane;
}

bool Board__get(Board* self, const Coordinates* location){
	/*
	 * Get whether the board is set to high at the coordinates.
	 *
	 * Args:
	 *	self: Board object whose location will be checked.
	 *	location: The xyz coordinates to look at.
	 *
	 * Returns:
	 *	A boolean on whether the board is set to high.
	 */
	if (!self)
	{
		return NULL;
	}
	unsigned int y = location->y;
	unsigned int z = location->z;
	return (bool)((self->bitboard[location->x] & get_yz_integer(y, z)) >> get_bit_shifted_value(y, z));
}

Coordinates* Board__get_first_instance(const Board* board)
{
	/*
	 * Retrieves the first coordinate where the bitboard is set to high.
	 *	This is the first instance we see the piece. Useful for King moves
	 *	because there is always only one so it is faster.
	 *
	 * Args:
	 *	board: The bitboard for a specific piece.
	 *
	 * Returns:
	 *	A CoordinateList (linked list of Coordinates) where the piece exists
	 *	in the overall board.
	 */
	int index = -1;
	int x = 0;
	for (x = 0; x < BOARD_SIZE; x++)
	{
		if (board->bitboard[x] == 0) continue;
		uint64_t plane = (board->bitboard[x]);
		index = 0;
		while (plane != 1)
		{
			plane = plane >> 1;
			index++;
		}
		break;
	}
	int y = index / BOARD_SIZE;
	int z = index % BOARD_SIZE;
	return Coordinates__create(x, y, z);
}

CoordinateList* Board__get_all_instances(const Board* board)
{
	/*
	 * Retrieves all coordinates where the bitboard is set to high.
	 *	This is where all instances of the piece are.
	 *
	 * Args:
	 *	board: The bitboard for a specific piece.
	 *
	 * Returns:
	 *	A CoordinateList (linked list of Coordinates) where the piece exists
	 *	in the overall board.
	 */
	CoordinateList* list = CoordinateList__create(NULL);
	int index = 0;
	int x = 0;
	int y = 0;
	int z = 0;
	for (x = 0; x < BOARD_SIZE; x++)
	{
		if (board->bitboard[x] == 0) continue;
		uint64_t plane = (board->bitboard[x]);
		index = 0;
		while (plane != 1)
		{
			plane = plane >> 1;
			index++;
		}
		y = index / BOARD_SIZE;
		z = index % BOARD_SIZE;
		Coordinates* coordinates = Coordinates__create(x, y, z);
		CoordinateNode* node = CoordinateNode__create(coordinates);
		CoordinateList__add_node(list, node);
	}

	return list;
}