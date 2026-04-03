#include <stdbool.h>
#include <string.h>
#include <sqlite3.h>
#include "constants.h"
#include "coordinates.h"
#ifndef SQL_DRIVER
#define SQL_DRIVER
sqlite3* DB;
char* db_name = "3dChess";
char* table_name = "moves";

char* exists_cmd = "SELECT EXISTS (SELECT * FROM %s M WHERE M.piece = %i AND M.x0 = %i AND M.y0 = %i AND M.z0 = %i AND M.x1 = %i AND M.y1 = %i AND M.z1 = %i";
int exists_cmd_length = strlen(exists_cmd) + strlen(table_name);

int open_db();
bool is_move_valid(Coordinates* start, Coordinates* end);
bool get_valid_moves(char piece, Coordinates* xyz, bool atk_ok);
void log_move();
#endif
