#include <stdlib.h>
#include "game_state.h"

struct Game{
	GameState game_state;
};

DEFAULT_FILEPATH = "initial_save_file.bin"

void Game__init(Game* game, char* filepath){
	// load file contents
	// parse out game state
	// create game state obj
	// validate game_state?
	// set other variables
}
Game* Game__create(char* filepath){
	Game* game = (Game*) malloc(sizeof(Game));
	if(filepath == NULL){
		filepath = DEFAULT_FILEPATH;
	}
	Game__init(game, filepath);
}
bool Game__move(Game* game, Coordinates* start, Coordinates* end){
	// chech if move is valid?
	// make move?
}
void Game__loop(Game* game){
	// while game is running
	// while move has value
	// copy move into new variable
	// set instance variable to none
	// check if move is valid
	// 	check if in bounds
	// 	pull piece
	// 	check if right color
	// 	if the current player is in checkmate
	// 		if so, can only use saved checkmate moves
	// 	if not, then do normal move
	// 		pull all moves for that piece
	//		filter out all moves in the same color
	//		check if there are any moves left
	//	check if the current end move is in the pool of valid moves
	//	if so, make the move
	//	check if opposite king is in checkmate
	//	if so, check valid moves in checkmate
	//	if none, then end game
	//	then, repeat while
}
void Game__save(Game* game, char* filepath){
	// save game state and anything else
	// maybe also save moves
}
