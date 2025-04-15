#include <stdint.h>

#define FULL_LAYER 0xffffffffffffffff

typedef struct board{
    uint64_t b[8]; // the actual board
    char rep; // the char that represents the pieces in this board
};

typedef struct game_state
{
    struct board white_pieces;
    struct board black_pieces;
    // maybe put white and black pieces in their own section
    struct board bw;
    struct board bb;

    struct board tw;
    struct board tb;

    struct board rw;
    struct board rb;

    struct board nw;
    struct board nb;

    struct board pw;
    struct board pb;

    struct board dw;
    struct board db;

    struct board kw;
    struct board kb;

    struct board qw;
    struct board qb;

    struct board iw;
    struct board ib;
    
    struct board gw;
    struct board gb;

    struct board ww;
    struct board wb;

    struct board dw;
    struct board db;

    // boolean
    char white_turn;
    // boolean array
    char castling;
    union en_p{
        char en_passant[3];
        struct coords{
            uint8_t x;
            uint8_t y;
            uint8_t z;
        }xyz;
        
    }en_passant;

    char half_move;

    uint16_t full_move;

};

extern struct game_state *game;


// functions
void init_game();