
#include <stdbool.h>
#include <sqlite3.h>
#include "constants.h"
#include "coordinates.h"
#include "sql_driver.h"

int open_db(){
	/*
	 * Opens the database.
	 */
	int exit = 0;
	exit = sqlite3_open(DB_PATH, &DB);
	return exit;
}

int exists_callback(void* data, int argc, char** argv, char** azColName){
	int *exists = (int*) data;
	if (argv[0] == 1){
		*exists = 1;
	}
	return 1;
}

bool is_move_valid(char piece, Coordinates* start, Coordinates* end){
	/*
	 * Checks if the move for the given piece is a valid move.
	 *
	 * Args:
	 * 	piece: the piece that is making the move.
	 * 	start: The coordinates of that piece.
	 * 	end: The destination coordinate.
	 *
	 * Return:
	 * 	Whether the move is valid.
	 */
	char* err_msg = 0;
	int found = 0;
	char exists_cmd_populated[exists_cmd_length];
	sprintf(&exists_cmd_populated, exists_cmd, table_name, piece, start.x, start.y, start.z, end.x, end.y, end.z);
	sqlite3_exec(&DB, exists_cmd_populated, exists_callback, &found, &err_msg);
	return found;
}
bool get_valid_moves(char piece, Coordinates* xyz, bool atk_ok);
void log_move();
