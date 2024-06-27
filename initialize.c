#include "game_state.h"

void init_game(){
    struct game_state *game = (struct game *) malloc(sizeof(struct game_state)); 

    // Declare Board
    // game->white_pieces->b = {FULL_LAYER,FULL_LAYER,0,0,0,0,0,0};
    struct board game_board_w = {.b={FULL_LAYER,FULL_LAYER,0,0,0,0,0,0}, .rep = 'x'};
    struct board game_board_b = {.b={0,0,0,0,0,0,FULL_LAYER,FULL_LAYER}, .rep = 'x'};
    game->white_pieces = game_board_w;
    game->black_pieces = game_board_b;

    /*
    Declaring Pieces
        White pieces are represented by lowercase letters
        Black pieces are represented by uppercase letters
    */ 

    // Bishop Declarations
    struct board bishop_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'b'};
    struct board bishop_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'B'};
    game->bw = bishop_w;
    game->bb = bishop_b;

    // Priest Declarations
    struct board priest_w = {.b={0,0,0,0,0,0,0,0}, .rep = 't'};
    struct board priest_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'T'};
    game->tw = priest_w;
    game->tb = priest_b;

    // Rook Declarations
    struct board rook_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'r'};
    struct board rook_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'R'};
    game->rw = rook_w;
    game->rb = rook_b;

    // Knight Declarations
    struct board knight_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'n'};
    struct board knight_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'N'};
    game->nw = knight_w;
    game->nb = knight_b;

    // Paladin Declarations
    struct board paladin_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'p'};
    struct board paladin_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'P'};
    game->pw = paladin_w;
    game->pb = paladin_b;

    // Dragon Declarations
    struct board dragon_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'd'};
    struct board dragon_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'D'};
    game->dw = dragon_w;
    game->db = dragon_b;

    // King Declarations
    struct board king_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'k'};
    struct board king_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'K'};
    game->kw = king_w;
    game->kb = king_b;

    // Queen Declarations
    struct board queen_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'q'};
    struct board queen_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'Q'};
    game->qw = queen_w;
    game->qb = queen_b;

    // Pawn
    struct board pawn_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'i'};
    struct board pawn_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'I'};
    game->iw = pawn_w;
    game->ib = pawn_b;

    // General Declarations
    struct board general_w = {.b={0x8100000000000081,0,0,0,0,0,0,0}, .rep = 'g'};
    struct board general_b = {.b={0,0,0,0,0,0,0,8100000000000081}, .rep = 'G'};
    game->gw = general_w;
    game->gb = general_b;

    // Wizard Declarations
    struct board wizard_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'w'};
    struct board wizard_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'W'};
    game->ww = wizard_w;
    game->wb = wizard_b;

    // Duke Declarations
    struct board duke_w = {.b={0,0,0,0,0,0,0,0}, .rep = 'u'};
    struct board duke_b = {.b={0,0,0,0,0,0,0,0}, .rep = 'U'};
    game->dw = duke_w;
    game->db = duke_b;
    
    // initialize other game data
    game->half_move = 0;
    game->full_move = 0;

    game->castling = ~0;

    game->white_turn = 'w';
    
    game->en_passant.xyz.x = 0;
    game->en_passant.xyz.y = 0;
    game->en_passant.xyz.z = 0;
}