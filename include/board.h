#include <stdint.h>
#include <stdbool.h>
#include "coordinates.h"
#ifndef BOARD
#define BOARD

typedef struct Board Board;

void set(Coordinates* location);
void unset(Coordinates* location);
bool get(Coordinates* location);
#endif
