
typedef struct board{
    long long unsigned int b[8]; // the actual board
    char rep; // the char that represents the pieces in this board
};

// overall game board
extern struct board game_board;

// Boards per piece

// Straight pieces
// Bishop
extern struct board bishop_w;
extern struct board bishop_b;

// Priest
extern struct board priest_w;
extern struct board priest_b;

// Rook
extern struct board rook_w;
extern struct board rook_b;

// L pieces (Knight-like)
// Knight
extern struct board knight_w;
extern struct board knight_b;

// Paladin
extern struct board paladin_w;
extern struct board paladin_b;

// Dragon
extern struct board dragon_w;
extern struct board dragon_b;

// Unique Pieces
// King
struct board king_w;
struct board king_b;

// Queen
struct board queen_w;
struct board queen_b;

// Pawn
struct board pawn_w;
struct board pawn_b;

// functions
void init_game();