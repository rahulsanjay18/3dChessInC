//
// Created by rahul on 4/23/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include "save_file.h"
#include "game_state.h"
#include "constants.h"

const int MAX_CAPTURED_PIECES_DIGITS = 2;
char WHITE = 'w';
char BLACK = 'b';
const int board_string_len = BOARD_SIZE*BOARD_SIZE*BOARD_SIZE + 2*BOARD_SIZE - 1;
const int captured_piece_string_len = (MAX_CAPTURED_PIECES_DIGITS+1)*SIZE_OF_CHARACTER_MAP-1;
int castle_str_len =(CASTLES*3)/2;

char* get_board_string(Boards* boards)
{

    char* board_string = (char*)malloc(board_string_len * sizeof(char));

    int string_index = 0;
    for (int z=0; z < BOARD_SIZE; z++)
    {
        for (int x=0; x < BOARD_SIZE; x++)
        {
            for (int y=0; y < BOARD_SIZE+1; y++)
            {
                if (y == BOARD_SIZE)
                {
                    board_string[string_index] = '/';
                }else
                {
                    const Coordinates* c = Coordinates__create(x,y,z);
                    board_string[string_index] = Boards__get_piece(boards, c);

                }
                string_index++;
            }
            if (x == BOARD_SIZE-1)
            {
                string_index--;
            }
        }
        board_string[string_index] = '\n';
        string_index++;
    }
    return board_string;
}

char* get_captured_piece_string(const int* captured_pieces)
{

    char* captured_piece_string = (char*)malloc(captured_piece_string_len * sizeof(char));

    char*ptr = captured_piece_string;
    for (int i=0; i<SIZE_OF_CHARACTER_MAP; i++)
    {
        ptr += sprintf(ptr, "%d/", captured_pieces[i]);
    }
    captured_piece_string[captured_piece_string_len-1] = '\n';
    return captured_piece_string;
}

char* get_castle_string(const bool* castle_status)
{

    char* castle_str = (char*)malloc(sizeof(char)*castle_str_len);
    for (int i=0; i < castle_str_len; i+=3)
    {
        castle_str[i] = castle_status[i] ? '1':'0';
        castle_str[i+1] = castle_status[i+1] ? '1':'0';
        castle_str[i+2]='\n';
    }
    return castle_str;
}

void save_file(GameState* game_state, const char* filepath)
{
    // Create and open a file in write mode
    FILE* fptr = fopen(filepath, "w");

    // Check if file opened successfully
    if (fptr == NULL) {
        printf("Error: Could not create file.\n");
        return;
    }

    Boards* boards = (Boards*) game_state->boards;
    int* captured_pieces=game_state->captured_pieces;
    bool is_white_turn = game_state->is_white_turn;
    bool is_check = game_state->is_check;
    bool is_checkmate = game_state->is_checkmate;
    bool* castle_status = game_state->castle_status;

    char* board_string = get_board_string(boards);

    // Write board string to the file
    fprintf(fptr, "%s", board_string);
    free(board_string);

    char* captured_piece_string=get_captured_piece_string(captured_pieces);
    fprintf(fptr, "%s", captured_piece_string);
    free(captured_piece_string);

    char* castle_str = get_castle_string(castle_status);

    fprintf(fptr, "%s", castle_str);
    free(castle_str);

    char turn_color = is_white_turn?WHITE:BLACK;
    fprintf(fptr, "%c\n", turn_color);

    const char is_in_check = is_check ? '+' : '0';
    const char is_check_or_mate = is_checkmate ? '#' : is_in_check;
    fprintf(fptr, "%c\n", is_check_or_mate);



    // Close the file
    fclose(fptr);

}

char* parse_board_string(const char* board_string)
{
    return NULL;
}

char* parse_captured_piece_string(const char* captured_piece_string)
{
    return NULL;
}

char* parse_castle_string(const char* castle_string)
{
    return NULL;
}

GameState* load_file(char* filepath)
{
    return (GameState*) NULL;
}