#ifndef CONST
#define CONST
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
int piece_char_to_int(char c);
#define SIZE_OF_CHARACTER_MAP 26
#define BOARD_SIZE 8
#define CASTLES 8
#endif
