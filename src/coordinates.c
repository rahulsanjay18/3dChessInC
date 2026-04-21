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

void Coordinates__destroy(Coordinates** coordinates){
	/*
	 * Deletes the coordinates object.
	 *
	 */
	if(*coordinates){
		free(*coordinates);
		*coordinates=NULL;
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

void CoordinateNode__destroy(CoordinateNode** c)
{
	if (*c){
		free(*(c));
		*c=NULL;
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
		result->len++;
	}
}

CoordinateList* CoordinateList__create(CoordinateNode* node)
{
	CoordinateList* result = (CoordinateList*) malloc(sizeof(CoordinateList));
	CoordinateList__init(result,node);
	return result;
}

void CoordinateList__destroy(CoordinateList** list)
{
	if(*list){
		free(*list);
		*list=NULL;
	}

}

void CoordinateList__add_node(CoordinateList* list, CoordinateNode* node)
{
	CoordinateNode* item = list->head;
	if (list->head == NULL)
	{
		list->head = node;
		list->len++;
		return;
	}
	while (item->next)
	{
		item = item->next;
	}

	item->next = node;
	list->len++;
}
void CoordinateList__delete_node(CoordinateList* list, CoordinateNode* node)
{
	CoordinateNode* item = list->head;
	if (list->head->next == NULL)
	{
		list->head = NULL;
		list->len--;
		CoordinateNode__destroy(&node);
		return;
	}
	if (node == list->head)
	{
		list->head = item->next;
	}else
	{
		while (item->next != node)
		{
			item = item->next;
		}
	}


	CoordinateNode* temp = item->next;
	item->next = item->next->next;
	temp->next = NULL;
	Coordinates__destroy(&(temp->c));
	CoordinateNode__destroy(&node);
	list->len--;
}
void CoordinateList__delete_node_with_coordinate_value(CoordinateList* list, const Coordinates* coords)
{
	CoordinateNode* item = list->head;
	if (item->c->x == coords->x && item->c->y == coords->y && item->c->z == coords->z)
	{
		list->head = item->next;
	}else
	{
		while (!(item->next->c->x == coords->x && item->next->c->y == coords->y && item->next->c->z == coords->z))
		{
			item = item->next;
		}
	}
	CoordinateNode* temp = item->next;
	item->next = item->next->next;
	temp->next = NULL;
	Coordinates__destroy(&(temp->c));
	list->len--;
}
CoordinateNode* CoordinateList__retrieve_node_from_index(const CoordinateList* list, int index)
{
	if ((index >= list->len) ||	index < 0)
	{
		return NULL;
	}
	CoordinateNode* item = list->head;
	while (index > 0)
	{
		item = item->next;
		index--;
	}
	return item;
}
CoordinateNode* CoordinateList__pop_front(CoordinateList* list)
{
	CoordinateNode* node = list->head;
	if (node)
	{
		list->head = list->head->next;
		node->next = NULL;
		list->len--;
	}
	return node;
}