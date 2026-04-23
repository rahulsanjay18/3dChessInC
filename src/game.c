#include <stdlib.h>
#include "game_state.h"
#include "game.h"

#include <stdio.h>

#include "save_file.h"
#include "sql_driver.h"

char* DEFAULT_FILEPATH = "game_start.txt";

void Game__init(Game* game, char* filepath, bool isTesting){
	if (!game || !filepath)
	{
		return;
	}
	// load file contents
	// parse out game state
	game->game_state = *load_file(filepath);
	game->piece_to_move = '\0';
	open_db(isTesting);
}
Game* Game__create(char* filepath, bool isTesting){
	Game* game = (Game*) malloc(sizeof(Game));
	if(filepath == NULL){
		filepath = DEFAULT_FILEPATH;
	}
	Game__init(game, filepath, isTesting);
	return game;
}
bool Game__move(Game* game, const Coordinates* start, const Coordinates* end){
	return make_move_with_coords(&game->game_state, start, end);
}

bool Game__move_with_piece(const Game* game, const char piece, const Coordinates* start, const Coordinates* end)
{
	return make_move_with_piece(&game->game_state, piece, start, end);
}

void Game__loop(Game* game){
	while (!game->game_state.is_checkmate)
	{
		while (game->start_move != NULL && game->end_move != NULL)
		{
			bool move_success = false;
			if (game->piece_to_move != '\0')
			{
				move_success = Game__move_with_piece(game, game->piece_to_move, game->start_move, game->end_move);
			}else
			{
				move_success = Game__move(game, game->start_move, game->end_move);
			}
			if (!move_success)
			{
				printf("Move failed.");
				continue;
			}
			// check for checks and mate


			game->game_state.is_white_turn = !game->game_state.is_white_turn;
		}
	}
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
