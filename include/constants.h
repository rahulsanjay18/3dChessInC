#ifndef CONST
#define CONST
#include <stdbool.h>
#include "coordinates.h"
#define SIZE_OF_CHARACTER_MAP 25
#define BOARD_SIZE 8
#define CASTLES 8
#define DIMENSIONS 3
#define NUM_ROOK_VECTORS 6
#define NUM_PRIEST_VECTORS 12
#define NUM_BISHOP_VECTORS 8
extern const char CHARACTER_MAP[];
const char WHITE_ROOK='r';
const char WHITE_PRIEST='t';
const char WHITE_BISHOP='b';
const char WHITE_QUEEN='q';
const char WHITE_KNIGHT='n';
const char WHITE_PALADIN='p';
const char WHITE_DRAGON='d';
const char WHITE_PAWN='i';
const char WHITE_GENERAL = 'g';
const char WHITE_DUKE = 'u';
const char WHITE_WIZARD = 'w';
const char WHITE_KING='k';

const char BLACK_ROOK='r';
const char BLACK_PRIEST='t';
const char BLACK_BISHOP='b';
const char BLACK_QUEEN='q';
const char BLACK_KNIGHT='n';
const char BLACK_PALADIN='p';
const char BLACK_DRAGON='d';
const char BLACK_PAWN='i';
const char BLACK_GENERAL = 'g';
const char BLACK_DUKE = 'u';
const char BLACK_WIZARD = 'w';
const char BLACK_KING='k';
extern const char DB_PATH[];
extern const char TEST_DB_PATH[];

static const int ROOK_VECTORS[NUM_ROOK_VECTORS][DIMENSIONS] = {{1, 0, 0}, {0,1,0}, {0,0,1}, {-1, 0,0}, {0,-1,0}, {0,0,-1}};
static const int PRIEST_VECTORS[DIMENSIONS][NUM_PRIEST_VECTORS/DIMENSIONS][DIMENSIONS] = {
    {{0, 1, 1}, {0, 1, -1}, {0, -1, 1}, {0, -1, -1}},
    {{1, 0, 1}, {1, 0, -1}, {-1, 0, 1}, {-1, 0, -1}},
    {{1, 1, 0}, {1, -1, 0}, {-1, 1, 0}, {-1, -1, 0}}
};
static const int BISHOP_VECTORS[NUM_BISHOP_VECTORS][DIMENSIONS] = {
    {1, 1, 1},
    {1, 1, -1},
    {1, -1, 1},
    {1, -1, -1},
    {-1, 1, 1},
    {-1, 1, -1},
    {-1, -1, 1},
    {-1, -1, -1}
};
int piece_char_to_int(char c);
bool is_piece_white(char c);
bool is_piece_black(char c);
Coordinates* get_rook_vector_index(const Coordinates* c);
Coordinates* get_priest_vector_index(const Coordinates* c);
Coordinates* get_bishop_vector_index(const Coordinates* c);
bool is_face_piece(char c);
bool is_edge_piece(char c);
bool is_vertex_piece(char c);
bool is_knightlike(char c);
#endif
