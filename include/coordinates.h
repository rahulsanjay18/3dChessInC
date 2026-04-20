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
#endif
