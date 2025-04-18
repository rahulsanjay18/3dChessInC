#include <stdint.h>
#include <stdbool.h>
#include "coordinates.h"
#include "board.h"

struct Board{
	uint64_t bitboard[8];
	char representing_character;
};

void set(Coordinates* location);
void unset(Coordinates* location);
bool get(Coordinates* location);
