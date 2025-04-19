#include <stdbool.h>
#include "coordinates.h"
#ifndef SQL_DRIVER
#define SQL_DRIVER
char* db_path;

bool is_move_valid(Coordinates* start, Coordinates* end);
bool get_valid_moves(char piece, Coordinates* xyz, bool atk_ok);
void log_move();
#endif
