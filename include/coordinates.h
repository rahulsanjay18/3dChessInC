#ifndef COORDS
#define COORDS
typedef struct Coordinates{
	int x;
	int y;
	int z;
}Coordinates;

typedef struct CoordinateNode
{
	struct CoordinateNode* next;
	Coordinates* c;

}CoordinateNode;

typedef struct CoordinateList{
	CoordinateNode* head;
	int len;
}CoordinateList;
Coordinates* Coordinates__create(int x, int y, int z);
void Coordinates__destroy(Coordinates* coordinates);
CoordinateNode* CoordinateNode__create(Coordinates* c);
void CoordinateNode__destroy(CoordinateNode* c);
CoordinateList* CoordinateList__create(CoordinateNode* node);
void CoordinateList__destroy(CoordinateList* coordinates);
void CoordinateList__add_node(CoordinateList* list, CoordinateNode* node);
void CoordinateList__delete_node(CoordinateList* list, CoordinateNode* node);
void CoordinateList__delete_node_with_coordinate_value(CoordinateList* list, Coordinates* coords);
CoordinateNode* CoordinateList__retrieve_node_from_index(CoordinateList* list, int index);
CoordinateNode* CoordinateList__pop_front(CoordinateList* list);
#endif
