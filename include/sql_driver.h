#pragma once
#include <stdbool.h>
#include "sqlite3.h"
#include "constants.h"
#include "coordinates.h"
#ifndef SQL_DRIVER
#define SQL_DRIVER

int open_db(bool isTesting);
bool is_move_possible(char piece, const Coordinates* start, const Coordinates* end);
CoordinateList* get_possible_moves(char piece, const Coordinates* xyz);
void log_move();
int close_db();
#endif
