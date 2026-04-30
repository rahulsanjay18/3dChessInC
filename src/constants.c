#include "constants.h"
#include <stdbool.h>
#include <stdlib.h>

#include "coordinates.h"
const char CHARACTER_MAP[] = "rRtTbBpPdDnNkKqQiIgGwWuU";
const char STRAIGHT_PIECES[] = "rRtTbBqQ";

const char DB_PATH[] = "../../db/3DChess.db";
const char TEST_DB_PATH[] = "../db/3DChess.db";
int piece_char_to_int(const char c){
	for (int i = 0; i < SIZE_OF_CHARACTER_MAP; i++){
		if(CHARACTER_MAP[i] == c){
			return i;
		}
	}

	return -1;
}
bool is_piece_white(const char c)
{
	return c <= 'z' && c >= 'a';
}

bool is_piece_black(const char c)
{
	return c <= 'z' && c >= 'a';
}

Coordinates* get_rook_vector_index(const Coordinates* c)
{
	/*
	 * Get hashing function for the rook direction vector.
	 * This is done by finding the nonzero coordinate, and then checking if that
	 * coordinate is negative or positive.
	 *
	 * Args:
	 *	c: the coordinates object representing the difference between start and end in the move.
	 */
	if (!(c->x || c->y || c->z))
	{
		return 0;
	}
	int index;
	int coord;
	if (c->x)
	{
		index = 0;
		coord = c->x;
	}else if (c->y)
	{
		index = 1;
		coord = c->y;
	}else
	{
		index = 2;
		coord = c->z;
	}

	index += (coord > 0) ? : (NUM_ROOK_VECTORS / 2);

	const int* vector = ROOK_VECTORS[index];

	return Coordinates__create(vector[0], vector[1], vector[2]);
}

Coordinates* get_priest_vector_index(const Coordinates* c)
{
	if (!(!c->x || !c->y || !c->z))
	{
		return 0;
	}
	int index0;
	int coord1, coord2;
	if (!c->x)
	{
		index0 = 0;
		coord1 = c->y;
		coord2 = c->z;
	}else if (!c->y)
	{
		index0 = 1;
		coord1 = c->x;
		coord2 = c->z;
	}else
	{
		index0 = 2;
		coord1 = c->x;
		coord2 = c->y;
	}

	int index1 = (coord1 > 0) ? 0 : (NUM_PRIEST_VECTORS / DIMENSIONS) / 2;
	index1 += coord2 <= 0;

	const int* vector = PRIEST_VECTORS[index0][index1];

	return Coordinates__create(vector[0], vector[1], vector[2]);
}

Coordinates* get_bishop_vector_index(const Coordinates* c)
{
	// all values must be nonzero
	if (!(c->x && c->y && c->z))
	{
		return 0;
	}

	if (!(abs(c->x) == abs(c->y) && abs(c->z) == abs(c->y)))
	{
		return 0;
	}

	int index = (c->x < 0) << 3 | (c->y < 0) << 2 | (c->z < 0);

	const int* vector = BISHOP_VECTORS[index];

	return Coordinates__create(vector[0], vector[1], vector[2]);
}

bool is_face_piece(const char piece)
{
	return piece == WHITE_ROOK ||
		piece == WHITE_QUEEN ||
			piece == BLACK_QUEEN ||
				piece == BLACK_ROOK ||
					piece == BLACK_KING ||
						piece == WHITE_KING ||
							piece == WHITE_DUKE ||
								piece==BLACK_DUKE ||
									piece == WHITE_GENERAL ||
										piece == BLACK_GENERAL;
}

bool is_edge_piece(const char piece)
{
	return piece == WHITE_PRIEST ||
		piece == WHITE_QUEEN ||
			piece == BLACK_QUEEN ||
				piece == BLACK_PRIEST ||
					piece == BLACK_KING ||
						piece == WHITE_KING||
							piece == WHITE_DUKE ||
								piece==BLACK_DUKE||
									piece==WHITE_WIZARD ||
										piece==BLACK_WIZARD;
}

bool is_vertex_piece(const char piece)
{
	return piece == WHITE_BISHOP ||
		piece == WHITE_QUEEN ||
			piece == BLACK_QUEEN ||
				piece == BLACK_BISHOP ||
					piece == BLACK_KING ||
						piece == WHITE_KING ||
							piece==WHITE_WIZARD ||
								piece==BLACK_WIZARD ||
									piece == WHITE_GENERAL ||
										piece == BLACK_GENERAL;
}

bool is_knightlike(const char piece)
{
	return piece == WHITE_KNIGHT ||
		piece == BLACK_KNIGHT ||
			piece == WHITE_PALADIN ||
				piece == BLACK_PALADIN ||
					piece == WHITE_DRAGON ||
						piece == BLACK_DRAGON;
}