#ifndef CONST
#define CONST
extern const char CHARACTER_MAP[];
const char WHITE_KING;
const char BLACK_KING;
extern const char DB_PATH[];
extern const char TEST_DB_PATH[];
int piece_char_to_int(char c);
#define SIZE_OF_CHARACTER_MAP 26
#define BOARD_SIZE 8
#define CASTLES 8
#endif
