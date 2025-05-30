#include <stdbool.h>
#include <sqlite3.h>
#include "constants.h"
#include "coordinates.h"
#ifndef SQL_DRIVER
#define SQL_DRIVER
sqlite3* DB;

int open_db();
bool is_move_valid(Coordinates* start, Coordinates* end);
bool get_valid_moves(char piece, Coordinates* xyz, bool atk_ok);
void log_move();
#endif
