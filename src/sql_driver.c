#include <stdio.h>
#include <stdbool.h>
#include "sqlite3.h"
#include <string.h>
#include "constants.h"
#include "coordinates.h"
#include "sql_driver.h"
#include <stdlib.h>
sqlite3* DB;
char* db_name = "3dChess";
char* table_name = "moves";

char* exists_cmd = "SELECT EXISTS (SELECT * FROM %s M WHERE M.piece = '%c' AND M.x0 = %i AND M.y0 = %i AND M.z0 = %i AND M.x1 = %i AND M.y1 = %i AND M.z1 = %i)";


int open_db(bool isTesting){
	/*
	 * Opens the database.
	 */
	int exit = 0;
	if (isTesting)
	{
		exit = sqlite3_open(TEST_DB_PATH, &DB);
	}else
	{
		exit = sqlite3_open(DB_PATH, &DB);
	}
	return exit;
}

int exists_callback(void* data, int argc, char** argv, char** azColName){
	int *exists = (int*) data;
	if (*argv[0] == '1'){
		*exists = 1;
	}
	return 1;
}

int moves_callback(void* datum, int count, char** data, char** columns)
{

	return 0;
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
	int exists_cmd_length = (int) (strlen(exists_cmd) + strlen(table_name));
	char *exists_cmd_populated=malloc(exists_cmd_length * sizeof(char));
	sprintf(exists_cmd_populated, exists_cmd, table_name, piece, start->x, start->y, start->z, end->x, end->y, end->z);
	sqlite3_exec(DB, exists_cmd_populated, exists_callback, &found, &err_msg);
	return found;
}
CoordinateList* get_valid_moves(char piece, Coordinates* xyz){
	/*
	 * Retrieve the valid moves for a given piece.
	 *
	 * Args:
	 * 	piece: The piece that is set to move.
	 * 	xyz: The location of the piece on the board.
	 *
	 * Returns:
	 * 	A list of valid move coordinates for the given piece and location.
	 * 	Caller is responsible for freeing memory allocated.
	 */
	char* err_msg = 0;
	int found = 0;
	int exists_cmd_length = (int) (strlen(exists_cmd) + strlen(table_name));
	char *exists_cmd_populated=malloc(exists_cmd_length * sizeof(char));
	sprintf(exists_cmd_populated, exists_cmd, table_name, piece, xyz->x, xyz->y, xyz->z);
	sqlite3_exec(DB, exists_cmd_populated, exists_callback, &found, &err_msg);
	return (CoordinateList*)NULL;
}

void log_move(){
	/*
	 * Logs the move to a file.
	 */
}

int close_db(){
	/*
	 * Closes database
	 */
	int rc = sqlite3_close(DB);
	return rc;
} 
