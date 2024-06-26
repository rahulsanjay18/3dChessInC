#include "game_state.h"

void init_game(){

    // Declare Board
    struct board game_board = {.b={0,0,0,0,0,0,0,0}, .rep = 'x'};


    /*
    Declaring Pieces
        White pieces are represented by lowercase letters
        Black pieces are represented by uppercase letters
    */ 

    // Bishop Declarations
    struct board bishop_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'b'};
    struct board bishop_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'B'};

    // Priest Declarations
    struct board priest_w = {.b={0,0,0,0,0,0,0,0}, .rep = 't'};
    struct board priest_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'T'};

    // Rook Declarations
    struct board rook_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'r'};
    struct board rook_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'R'};

    // Knight Declarations
    struct board knight_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'n'};
    struct board knight_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'N'};

    // Paladin Declarations
    struct board paladin_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'p'};
    struct board paladin_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'P'};

    // Dragon Declarations
    struct board dragon_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'd'};
    struct board dragon_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'D'};

    // King Declarations
    struct board king_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'k'};
    struct board king_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'K'};

    // Queen Declarations
    struct board queen_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'q'};
    struct board queen_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'Q'};

}