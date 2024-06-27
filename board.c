#include "game_state.h"

void init_game(){

    // Declare Board
    struct board game_board = {.b={FULL_LAYER,FULL_LAYER,0,0,0,0,FULL_LAYER,FULL_LAYER}, .rep = 'x'};


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

    // Pawn
    struct board pawn_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'i'};
    struct board pawn_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'I'};

    // General Declarations
    struct board general_w = {.b={0x8100000000000081,0,0,0,0,0,0,0}, .rep = 'g'};
    struct board general_b = {.b={0,0,0,0,0,0,0,8100000000000081}, .rep = 'G'};

    // Wizard Declarations
    struct board wizard_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'w'};
    struct board wizard_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'W'};

    // Duke Declarations
    struct board duke_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'u'};
    struct board duke_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'U'};

}