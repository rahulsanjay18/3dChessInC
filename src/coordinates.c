#include <stdlib.h>
#include "coordinates.h"
void Coordinates__init(Coordinates* self, int x, int y, int z){
	self->x = x;
	self->y = y;
	self->z = z;
}

Coordinates* Coordinates__create(int x, int y, int z){
	Coordinates* result = (Coordinates*) malloc(sizeof(Coordinates));
	Coordinates__init(result, x, y, z);
	return result;
}

void Coordinates__destroy(Coordinates* coordinates){
	if(coordinates){
		free(coordinates);
	}
}
