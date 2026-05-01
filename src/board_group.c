#include <stdlib.h>
#include "constants.h"
#include "board.h"
#include "board_group.h"
#include "sql_driver.h"

void Boards__init(Boards* boards, const char* board_repr){
	/*
	 * Initializes elements of the Boards struct.
	 *
	 * Args:
	 *	boards: the struct to populate.
	 *	board_repr: An array where each entry is the character representation of a piece if it exists.
	 *		size of (BOARD_SIZE, BOARD_SIZE, BOARD_SIZE).
	 */
	if (!boards)
	{
		return;
	}
	for(int i = 0; i < SIZE_OF_CHARACTER_MAP; i++){
		const char repr = CHARACTER_MAP[i];
		Board* board = Board__create(repr, board_repr);
		boards->full_board[i] = board;
	}
}

Boards* Boards__create(const char* board_repr){
	/*
	 * Creates the board struct.
	 *
	 * Args:
	 *	board_repr: human readable board representation.
	 *
	 * Returns:
	 *	Pointer to Boards struct.
	 */
	Boards* result = (Boards*) malloc(sizeof(Boards));
	Boards__init(result, board_repr);
	return result;
}

void Boards__destroy(Boards** boards)
{
	/*
	 * Destroys the board struct.
	 *
	 * Args:
	 *	boards: The pointer to the pointer to the struct to destroy.
	 */
	if (!*boards) return;
	free(*boards);
	*boards = NULL;

}

void Boards__set_piece(Boards* boards, const char piece, const Coordinates* coordinates){
	/*
	 * Set the bitboard of the specified piece to one at a given location.
	 *
	 * Args:
	 *	boards: The boards struct to operate on.
	 *	piece: piece whose bitboard to access.
	 *	coordinates: xyz coordinates to one.
	 */
	if (!boards)
	{
		return;
	}
	const int index = piece_char_to_int(piece);
	Board* board = boards->full_board[index];
	Board__set(board, coordinates);
}

void Boards__unset_piece(Boards* boards, const char piece, const Coordinates* coordinates){
	/*
	 * Set the bitboard of the specified piece to zero at a given location.
	 *
	 * Args:
	 *	boards: The boards struct to operate on.
	 *	piece: piece whose bitboard to access.
	 *	coordinates: xyz coordinates to zero.
	 */
	if (!boards)
	{
		return;
	}
	const int index = piece_char_to_int(piece);
	Board* board = boards->full_board[index];
	Board__unset(board, coordinates);
}

void Boards__unset(Boards* boards, const Coordinates* coordinates){
	/*
	 * Set the bitboard of all pieces to zero at a given location.
	 *
	 * Args:
	 *	boards: The boards struct to operate on.
	 *	coordinates: xyz coordinates to zero.
	 */
	if (!boards)
	{
		return;
	}
	for(int i = 0; i < SIZE_OF_CHARACTER_MAP; i++)
	{	Board* board = boards->full_board[i];
		Board__unset(board, coordinates);
	}
}

char Boards__get_piece(Boards* boards, const Coordinates* coordinates){
	/*
	 * Retrieve piece at given location.
	 *
	 * Args:
	 *	boards: Boards struct to read.
	 *	coordinateS: the coordinates to retrieve the piece on.
	 *
	 * Returns:
	 *	Retrieves the character representation of the piece at the location.
	 */
	if (!boards)
	{
		return '\0';
	}
	for(int i = 0; i < SIZE_OF_CHARACTER_MAP; i++){
		if(Board__get(boards->full_board[i], coordinates)){
			return CHARACTER_MAP[i];
		}
	}
	return '\0';
}

bool Boards__check_piece_exists(Boards* boards, const char piece, const Coordinates* coordinates){
	/*
	 * Check if the given piece exists at the location.
	 *
	 * Args:
	 *	boards: Boards struct to read.
	 *	piece: the piece to look for.
	 *	coordinateS: the coordinates to retrieve the piece on.
	 *
	 * Returns:
	 *	Whether the piece is in the location specified.
	 */
	if (!boards)
	{
		return false;
	}
	const int index = piece_char_to_int(piece);

	return Board__get(boards->full_board[index], coordinates);
}

Coordinates* Boards__get_coordinates_first_instance(Boards* boards, const char piece)
{
	/*
	 * Retrieves the first coordinate where the bitboard for a given piece is set to high.
	 *	This is the first instance we see the piece. Useful for King moves
	 *	because there is always only one so it is faster.
	 *
	 * Args:
	 *	boards: The Boards object to read.
	 *	piece: the piece whose bitboard to pull.
	 *
	 * Returns:
	 *	A Coordinate where the piece exists in the overall board.
	 */
	if (!boards) return NULL;
	int index = piece_char_to_int(piece);

	Board* board = boards->full_board[index];
	return Board__get_first_instance(board);
}

CoordinateList* Boards__get_all_coordinates(Boards* boards, const char piece)
{
	/*
	 * Retrieves all coordinates where the bitboard for a given piece is set to high.
	 *	This is where all instances of the piece are.
	 *
	 * Args:
	 *	board: The bitboard for a specific piece.
	 *	piece: the piece whose bitboard to pull.
	 *
	 * Returns:
	 *	A CoordinateList (linked list of Coordinates) where the piece exists
	 *	in the overall board.
	 */
	if (!boards) return NULL;
	int index = piece_char_to_int(piece);

	Board* board = boards->full_board[index];
	return Board__get_all_instances(board);
}

bool check_square_is_moveable(Boards* boards, const char piece, const Coordinates* end)
{
	/*
	 * Checks if the square can be moved to.
	 * A square can be moved to if there is no piece there or if the
	 * piece is the opposite color (capture).
	 *
	 * Args:
	 *	boards: The Boards struct to read.
	 *	piece: the piece that is moving.
	 *	end: the coordinates that piece intends to move to.
	 *
	 * Returns:
	 *	If we are able to move a piece.
	 */
	char end_piece = Boards__get_piece(boards, end);
	if (end_piece)
	{
		return is_piece_white(piece) ^ is_piece_white(end_piece);
	}
	return true;
}


bool check_path_clear(Boards* boards, const char piece, const Coordinates* start, const Coordinates* end, const Coordinates* vector)
{
	/*
	 * Checks if the path between start and end coordinates is clear.
	 *
	 * Args:
	 *	boards: The Boards struct to read.
	 *	piece: the piece that is moving.
	 *	start: the location of the piece that is moving.
	 *	end: the coordinates that piece intends to move to.
	 *	vector: the direction the piece is going towards.
	 *
	 * Returns:
	 *	Whether the path is clear for the piece to move.
	 */
	Coordinates* current_coordinates = Coordinates__copy(start);

	// retrieve first nonempty coordinate if there is any
	while (Coordinates__is_equal(current_coordinates, end))
	{
		Coordinates__add(vector, current_coordinates);
		if (!Coordinates__is_equal(current_coordinates, end) && Boards__get_piece(boards, current_coordinates) != '\0') return false;
	}
	return check_square_is_moveable(boards, piece, end);
}

bool check_pawn_moves(Boards* boards, const char piece, const Coordinates* start, const Coordinates* diff, const Coordinates* end)
{
	/*
	 * Checks if the pawn can make its move.
	 *
	 * Args:
	 *	boards: The Boards struct to read.
	 *	piece: the pawn that is moving.
	 *	start: the location of the pawn that is moving.
	 *	diff: the direction the pawn is going towards.
	 *	end: the coordinates that pawn intends to move to.
	 *
	 * Returns:
	 *	Whether the pawn can make the move.
	 */

	// No attack pawn
	if (diff->x != 0 && diff->y == 0 && diff-> z == 0)
	{
		const int adder = (piece == WHITE_PAWN) ? 1 : -1;
		Coordinates* forward_move = Coordinates__copy(start);
		forward_move->x = start->x + adder;
		const char intermediary_piece = Boards__get_piece(boards, forward_move);

		// checks for special pawn first move
		if ((piece == WHITE_PAWN && start->x == 1 && diff->x == 2) || (piece==BLACK_PAWN && start->x == 6 && diff->x == -2))
		{
			forward_move->x = start->x + adder;
			const char end_piece = Boards__get_piece(boards, forward_move);
			return intermediary_piece == '\0' && end_piece == '\0';

		}

		return intermediary_piece == '\0';

	}

	return check_square_is_moveable(boards, piece, end);
}

bool is_move_valid(Boards* boards,const char piece, const Coordinates* start, const Coordinates* end)
{
	/*
	 * Checks if the move the player wants to make, can be made.
	 *
	 * Args:
	 *	boards: the Boards struct to read from.
	 *	piece: the piece that is moving.
	 *	start: the location of the piece that is moving.
	 *	end: where the piece is moving to.
	 *
	 * Returns:
	 *	If the move is valid and can be made or not.
	 */
	if (Coordinates__is_equal(start, end)) return false;
	bool is_possible = is_move_possible(piece, start, end);
	if (!is_possible) return false;

	Coordinates* diff = Coordinates__subtract(start, end);
	Coordinates* vector = NULL;
	// the next block covers:
	// - Rook
	// - Priest
	// - Bishop
	// - Queen
	// - King
	// - General
	// - Wizard
	// - Duke
	if (is_face_piece(piece))
	{
		vector = get_rook_vector_index(diff);
	}
	if (!vector && is_edge_piece(piece))
	{
		vector = get_priest_vector_index(diff);
	}
	if (!vector && is_vertex_piece(piece))
	{
		vector = get_bishop_vector_index(diff);
	}
	if (vector)
	{
		return check_path_clear(boards, piece, start, end, vector);
	}

	// This if statement covers:
	// - Knight
	// - Paladin
	// - Dragon
	if (is_knightlike(piece))
	{
		return check_square_is_moveable(boards, piece, end);
	}
	return check_pawn_moves(boards, piece, start, end, vector);

	// TODO: STILL NEED TO ACCOUNT FOR:
	// - Castling
	// - En Passant
}

bool make_move(Boards* boards, const char piece, const Coordinates* start, const Coordinates* end)
{
	/*
	 * Moves a piece.
	 *
	 * Args:
	 *	boards: the Boards struct to read from.
	 *	piece: the piece that is moving.
	 *	start: the location of the piece that is moving.
	 *	end: where the piece is moving to.
	 *
	 * Returns:
	 *	If the move has been made.
	 */
	// if in check, see if moves are in the check list
	bool is_valid = is_move_valid(boards, piece, start, end);
	if (!is_valid) return false;
	// check if move creates a check on its own king
	Boards__unset_piece(boards, piece, start);
	Boards__set_piece(boards, piece, end);
	// check if in check or mate
	return true;
}