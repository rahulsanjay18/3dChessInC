#include <stdlib.h>
#include "coordinates.h"
void Coordinates__init(Coordinates* self, int x, int y, int z){
	self->x = x;
	self->y = y;
	self->z = z;
}

Coordinates* Coordinates__create(int x, int y, int z){
	/*
	 * Create Coordinates object.
	 * 	The board is a lattice made up of cubes, and therefore has
	 * 	three different dimensions that need to be defined to specify
	 * 	a unique point.
	 *
	 * Args:
	 * 	x: the x coordinate.
	 * 		This can be visualized as the 'forward' direction.
	 * 	y: the y coordinate.
	 * 		This can be visualized as the 'rightward' direction. 
	 * 	z: the z coordinate.
	 * 		This can be visualized as the 'upward' direction.
	 *
	 * Returns:
	 * 	Created coordinates object.
	 */
	Coordinates* result = (Coordinates*) malloc(sizeof(Coordinates));
	Coordinates__init(result, x, y, z);
	return result;
}

void Coordinates__destroy(Coordinates* coordinates){
	/*
	 * Deletes the coordinates object.
	 *
	 */
	if(coordinates){
		free(coordinates);
	}
}
