#pragma once

#include "constants.h"
#include "coordinates.h"
#include "board.h"
#ifndef BOARDS
#define BOARDS

typedef struct Boards{
    Board* full_board[SIZE_OF_CHARACTER_MAP];
} Boards;

Boards* Boards__create(const char* board_repr);
void Boards__destroy(Boards** boards);
void Boards__set_piece(Boards* boards, char piece, const Coordinates* coordinates);
void Boards__unset_piece(Boards* boards, char piece, const Coordinates* coordinates);
void Boards__unset(Boards* boards, const Coordinates* coordinates);
char Boards__get_piece(Boards* boards, const Coordinates* coordinates);
bool Boards__check_piece_exists(Boards* boards, char piece, const Coordinates* coordinates);
Coordinates* Boards__get_coordinates_first_instance(Boards* boards, char piece);
CoordinateList* Boards__get_all_coordinates(Boards* boards, char piece);
bool is_move_valid(Boards* boards,char piece, const Coordinates* start, const Coordinates* end);
bool make_move(Boards* boards, char piece, const Coordinates* start, const Coordinates* end);
#endif
