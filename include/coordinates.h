#ifndef COORDS
#define COORDS
typedef struct Coordinates{
	int x;
	int y;
	int z;
}Coordinates;
Coordinates* Coordinates__create(int x, int y, int z);
void Coordinates__destroy(Coordinates* coordinates);
#endif
