#include <stdbool.h>
#include <sqlite3.h>
#include "constants.h"
#include "coordinates.h"
#ifndef SQL_DRIVER
#define SQL_DRIVER
sqlite3* DB;
char* db_name = "3dChess";
char* table_name = "moves";

char* exists_cmd = "SELECT EXISTS (SELECT * FROM %s M WHERE M.piece = %i AND M.x0 = %i AND M.y0 = %i AND M.z0 = %i AND M.x1 = %i AND M.y1 = %i AND M.z1 = %i";
static int exists_cmd_length = sizeof(*exists_cmd) + sizeof(*table_name);

int open_db();
bool is_move_valid(char piece, Coordinates* start, Coordinates* end);
Coordinates* get_valid_moves(char piece, Coordinates* xyz);
void log_move();
int close_db();
#endif
