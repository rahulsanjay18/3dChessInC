#include <stdio.h>
#include "sql_driver.h"
#include "coordinates.h"
/* main.c */
int main(int argc, char *argv[]) {
	open_db(false);
	Coordinates* start = Coordinates__create(0, 0, 0);
	Coordinates* end = Coordinates__create(1, 1, 0);
	const bool res = is_move_valid('r', start, end);
	printf("%i", res);
}
