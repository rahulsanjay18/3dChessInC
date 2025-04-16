#include <stdint.h>
#include "coordinates.h"
#include <stdbool.h>

struct Board;

void set(Coordinates* location);
void unset(Coordinates* location);
bool get(Coordinates* location);
