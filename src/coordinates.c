#include <stdlib.h>
#include "coordinates.h"

#include <stdbool.h>

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
	if(!*coordinates)return;
	free(*coordinates);
	*coordinates=NULL;
}

bool Coordinates__is_equal(const Coordinates* c1, const Coordinates* c2)
{
	/*
	 * Checks if two coordinates are equal.
	 *	That is, the x, y, and z coordinates match.
	 *
	 * Args:
	 *	c1: the first coordinate.
	 *	c2: the second coordinate.
	 *
	 * Returns:
	 *	True if the xyz coordinates match, False otherwise.
	 */
	return c1->x == c2->x && c1->y == c2->y && c1->z == c2->z;
}

Coordinates* Coordinates__add(const Coordinates* c1, const Coordinates* c2)
{
	/*
	 * Adds two coordinates together.
	 *
	 * Args:
	 *	c1: the first coordinate.
	 *	c2: the second coordinate.
	 *
	 * Returns:
	 *	Coordinate struct that is the sum of the two coordinates.
	 */
	return Coordinates__create(c2->x + c1->x, c2->y + c1->y, c2->z + c1->z);
}

Coordinates* Coordinates__subtract(const Coordinates* c1, const Coordinates* c2)
{
	/*
	 * Subtracts two coordinates.
	 *
	 * Args:
	 *	c1: the first coordinate.
	 *	c2: the second coordinate.
	 *
	 * Returns:
	 *	Coordinate struct that is the difference of the two coordinates.
	 */
	return Coordinates__create(c2->x - c1->x, c2->y - c1->y, c2->z - c1->z);
}

Coordinates* Coordinates__copy(const Coordinates* c)
{
	/*
	 * Copies a coordinate struct.
	 *
	 * Args:
	 *	c: the coordinate struct to copy.
	 *
	 * Returns:
	 *	Copy of the coordinate struct input.
	 */
	return Coordinates__create(c->x, c->y, c->z);
}

void CoordinateNode__init(CoordinateNode* result, Coordinates* c)
{
	/*
	 * Initializes coordinate node.
	 *
	 * Args:
	 *	result: Allocated CoordinateNode pointer.
	 *	c: Coordinate struct to populate the node with.
	 *		Can be NULL.
	 */

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
	/*
	 * Create CoordinateNode struct.
	 *
	 * Args:
	 *	c: Coordinate struct to populate node with.
	 *		Can be NULL.
	 *
	 * Returns:
	 *	Pointer to the newly created CoordinateNode.
	 */
	CoordinateNode* result = (CoordinateNode*) malloc(sizeof(CoordinateNode));
	CoordinateNode__init(result, c);

	return result;
}

void CoordinateNode__destroy(CoordinateNode** c)
{
	/*
	 * Destroys coordinate struct.
	 *
	 * Args:
	 *	c: Pointer to CoordinateNode pointer.
	 */
	if (!*c)return;
	free(*(c));
	*c=NULL;
}

bool CoordinateNode__compare_values(const CoordinateNode* node1, const CoordinateNode* node2)
{
	/*
	 * Checks if two coordinate nodes are equal.
	 *	That is, the x, y, and z coordinates match.
	 *
	 * Args:
	 *	node1: the first coordinate node.
	 *	node2: the second coordinate node.
	 *
	 * Returns:
	 *	True if the xyz coordinates match, False otherwise.
	 */

	return Coordinates__is_equal(node1->c, node2->c);
}

void CoordinateList__init(CoordinateList* result, CoordinateNode* node)
{
	if (!result) return;

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
	if(!*list)return;
	CoordinateNode* temp = (*list)->head;
	free(*list);
	*list=NULL;
	while (temp->next)
	{
		CoordinateNode__destroy(&temp);
		temp = temp->next;
	}
	CoordinateNode__destroy(&temp);
}

void CoordinateList__add_node(CoordinateList* list, CoordinateNode* node)
{
	if (!list) return;
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
	if ((index >= list->len) ||	index < 0) return NULL;
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

CoordinateList* CoordinateList__compute_intersection(const CoordinateList* list1, const CoordinateList* list2)
{
	CoordinateList* result = CoordinateList__create(NULL);
	for (int i = 0; i < list1->len; i++)
	{
		for (int j = i; j < list2->len; j++)
		{
			CoordinateNode* node = CoordinateList__retrieve_node_from_index(list1, i);
			CoordinateNode* node2 = CoordinateList__retrieve_node_from_index(list2, j);
			if (CoordinateNode__compare_values(node, node2))
			{
				CoordinateNode* common_element = CoordinateNode__create(node->c);
				CoordinateList__add_node(result, common_element);
			}
		}
	}
	return result;
}