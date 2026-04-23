//
// Created by rahul on 4/23/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include "save_file.h"

#include <string.h>

#include "game_state.h"
#include "constants.h"

const int MAX_CAPTURED_PIECES_DIGITS = 2;
char WHITE = 'w';
char BLACK = 'b';
const int board_string_len = BOARD_SIZE*BOARD_SIZE*BOARD_SIZE + 2*BOARD_SIZE;
const int captured_piece_string_len = (MAX_CAPTURED_PIECES_DIGITS+1)*SIZE_OF_CHARACTER_MAP-1;
int castle_str_len =CASTLES+1;
int turn_and_check_status_len = 3;
char CHECK = '+';
char CHECKMATE = '#';
char NO_CHECK_OR_MATE = '0';


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
    board_string[board_string_len-1] = '\0';
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
    for (int i=0; i < castle_str_len; i++)
    {
        castle_str[i] = castle_status[i] ? '1':'0';
    }
    castle_str[castle_str_len-1] = '\n';
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
    fprintf(fptr, "%c", turn_color);

    const char is_in_check = is_check ? '+' : '0';
    const char is_check_or_mate = is_checkmate ? '#' : is_in_check;
    fprintf(fptr, "%c\n", is_check_or_mate);

    // Close the file
    fclose(fptr);

}

void parse_board_string(char* board_string)
{
    char*dst;
    for (const char* src = dst = board_string; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != '/' || *dst != '\n') dst++;
    }
    *dst = '\0';
}

int* parse_captured_piece_string(char* captured_piece_string)
{
    int* captured_pieces = (int*)malloc(sizeof(int) * SIZE_OF_CHARACTER_MAP);
    int captured_piece_index = 0;
    for (int i =0; i<=captured_piece_string_len; i+=(MAX_CAPTURED_PIECES_DIGITS+1))
    {
        char num[MAX_CAPTURED_PIECES_DIGITS+1];
        memcpy(num, &captured_piece_string[i], sizeof(char)*MAX_CAPTURED_PIECES_DIGITS);
        num[MAX_CAPTURED_PIECES_DIGITS+1] = '\0';
        char* end;
        int num_pieces = (int)strtol(num, &end, 10);
        captured_pieces[captured_piece_index] = num_pieces;
        captured_piece_index++;
    }
    free(captured_piece_string);
    return captured_pieces;
}

bool* parse_castle_string(char* castle_string)
{
    bool* castle_status = (bool*)malloc(sizeof(bool) * CASTLES);
    for (int i=0; i < CASTLES; i++)
    {
        castle_status[i] = castle_string[i] == '1';
    }
    free(castle_string);
    return castle_status;
}

GameState* load_file(const char* filepath)
{
    // Create and open a file in write mode
    FILE* fptr = fopen(filepath, "w");

    // Check if file opened successfully
    if (fptr == NULL) {
        printf("Error: Could not create file.\n");
        return (GameState*) NULL;;
    }
    char* board_string = (char*) malloc(sizeof(char) * board_string_len);
    size_t bytesRead = fread(board_string, sizeof(char), board_string_len, fptr);
    board_string[bytesRead-1] = '\0';
    fptr += bytesRead;
    parse_board_string(board_string);

    char* captured_piece_string = (char*) malloc(sizeof(char) * captured_piece_string_len);
    bytesRead = fread(captured_piece_string, sizeof(char), captured_piece_string_len, fptr);
    int* captured_pieces = parse_captured_piece_string(captured_piece_string);
    fptr += bytesRead;

    char* castle_string = (char*) malloc(sizeof(char) * castle_str_len);
    bytesRead = fread(castle_string, sizeof(char), castle_str_len, fptr);
    castle_string[bytesRead-1] = '\0';
    bool* castles = parse_castle_string(castle_string);
    fptr+=bytesRead;

    char* turn_and_check_status = (char*) malloc(sizeof(char) * turn_and_check_status_len);
    fread(turn_and_check_status, sizeof(char), turn_and_check_status_len, fptr);

    bool is_white_turn = turn_and_check_status[0] == WHITE;;
    bool is_check = turn_and_check_status[1] != NO_CHECK_OR_MATE;
    bool is_checkmate = turn_and_check_status[1] == CHECKMATE;
    free(turn_and_check_status);

    GameState* state = GameState__create(board_string, captured_pieces, is_white_turn, castles, is_checkmate, is_check, false);

    return state;
}