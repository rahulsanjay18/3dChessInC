#include "constants.h"

int char_to_int(char c){
	for (int i = 0; i < SIZE_OF_CHARACTER_MAP; i++){
		if(CHARACTER_MAP[i] == c){
			return i;
		}
	}

	return -1;
}
