#include <stdlib.h>
#include "coordinates.h"
void Coordinates__init(Coordinates* self, const int x, const int y, const int z){
	if (!self)
	{
		return;
	}
	self->x = x;
	self->y = y;
	self->z = z;
}

Coordinates* Coordinates__create(const int x, const int y, const int z){
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

void CoordinateNode__init(CoordinateNode* result, Coordinates* c)
{
	if (!result)
	{
		return;
	}
	result->next = NULL;
	result->c = NULL;
	if (c)
	{
		result->c = c;
	}
}

CoordinateNode* CoordinateNode__create(Coordinates* c)
{
	CoordinateNode* result = (CoordinateNode*) malloc(sizeof(CoordinateNode));
	CoordinateNode__init(result, c);

	return result;
}

void CoordinateNode__destroy(CoordinateNode* c)
{
	if(c){
		free(c);
	}
}

void CoordinateList__init(CoordinateList* result, CoordinateNode* node)
{
	if (!result)
	{
		return;
	}
	result->head = NULL;
	result->len = 0;
	if (node)
	{
		result->head = node;
	}
}

CoordinateList* CoordinateList__create(CoordinateNode* node)
{
	CoordinateList* result = (CoordinateList*) malloc(sizeof(CoordinateList));
	CoordinateList__init(result,node);
	return result;
}

void CoordinateList__destroy(CoordinateList* coordinates)
{
	if(coordinates){
		free(coordinates);
	}

}