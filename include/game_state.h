#include <stdbool.h>
#include "constants.h"
#include "board_group.h"
#ifndef GAME_STATE
#define GAME_STATE
typedef struct GameState{ 
	char board_representation[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE];
	Boards* boards;
	int captured_pieces[SIZE_OF_CHARACTER_MAP];
	bool is_white_turn;
	bool* castle_status;
	bool is_checkmate;
}GameState;

GameState* GameState__create(char* board_repr[BOARD_SIZE][BOARD_SIZE], bool is_white_turn, bool castle_status[CASTLES], bool is_checkmate);
void make_move(GameState* game_state, Coordinates* start, Coordinates* end);
void pretty_print_board(GameState* game_state, char* board[BOARD_SIZE][BOARD_SIZE]);
int get_piece_num(GameState* game_state, Coordinates* location);
char get_piece_char(GameState* game_state, Coordinates* location);
#endif
