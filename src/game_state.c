#include <stdbool.h>
#include "constants.h"
#include "board_group.h"
struct GameState GameState{
	char board_representation[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE];
	int captured_pieces[SIZE_OF_CHARACTER_MAP];
	bool is_white_turn;
	bool castle_status[CASTLES];
	bool is_checkmate;
}

void make_move(Coordinates* start, Coordinates* end);
void pretty_print_board(char* board[BOARD_SIZE][BOARD_SIZE]);
int get_piece_num(Coordinates* location);
char get_piece_char(Coordinates* location);
void save(char* filepath);
void load(char* filepath);
