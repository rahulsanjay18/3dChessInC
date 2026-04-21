#pragma once
#include <stdbool.h>
#include "sqlite3.h"
#include "constants.h"
#include "coordinates.h"
#ifndef SQL_DRIVER
#define SQL_DRIVER

int open_db(bool isTesting);
bool is_move_valid(char piece, Coordinates* start, Coordinates* end);
CoordinateList* get_valid_moves(char piece, Coordinates* xyz);
void log_move();
int close_db();
#endif
