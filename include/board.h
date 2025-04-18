#include <stdint.h>
#include <stdbool.h>
#include "coordinates.h"

typedef struct Board Board;

void set(Coordinates* location);
void unset(Coordinates* location);
bool get(Coordinates* location);
