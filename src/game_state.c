#include <stdlib.h>
#include <stdbool.h>
#include "constants.h"
#include "board_group.h"
struct GameState{
	Boards* boards;
	int captured_pieces[SIZE_OF_CHARACTER_MAP];
	bool is_white_turn;
	bool castle_status[CASTLES];
	bool is_checkmate;
};

void GameState__init(GameState* game_state, char* board_repr[BOARD_SIZE][BOARD_SIZE], bool is_white_turn, bool castle_status[CASTLES], bool is_checkmate){
	game_state->boards = Boards__create(board_repr);
	game_state->is_white_turn = is_white_turn;
	game_state->castle_status = castle_status;
	game_state->is_checkmate = is_checkmate;
}
GameState* GameState__create(char* board_repr[BOARD_SIZE][BOARD_SIZE], bool is_white_turn, bool castle_status[CASTLES], bool is_checkmate){
	GameState* result = (GameState*) malloc(sizeof(GameState));
	
	GameState__init(game_state, board_repr[BOARD_SIZE][BOARD_SIZE], is_white_turn, castle_status[CASTLES], is_checkmate)
	return result;
}
void make_move(Coordinates* start, Coordinates* end);
void pretty_print_board(char* board[BOARD_SIZE][BOARD_SIZE]);
int get_piece_num(Coordinates* location);
char get_piece_char(Coordinates* location);
