#include "constants.h"
const char CHARACTER_MAP[] = "rRtTbBpPdDnNkKqQiIgGwWuU";
const char DB_PATH[] = "../../db/3DChess.db";
const char TEST_DB_PATH[] = "../db/3DChess.db";
int piece_char_to_int(const char c){
	for (int i = 0; i < SIZE_OF_CHARACTER_MAP; i++){
		if(CHARACTER_MAP[i] == c){
			return i;
		}
	}

	return -1;
}
