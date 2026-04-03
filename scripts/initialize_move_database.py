import sqlite3
from tqdm import tqdm
import sqlite_utils
from copy import deepcopy as copy
from itertools import permutations
#conn = sqlite3.connect('db/3DChess.db')
#c = conn.cursor()

#c.execute('''CREATE TABLE IF NOT EXISTS moves (
#    piece CHAR(1) NOT NULL,
#    x0 INTEGER NOT NULL,
#    y0 INTEGER NOT NULL,
#    z0 INTEGER NOT NULL,
#    x1 INTEGER NOT NULL,
#    y1 INTEGER NOT NULL,
#    z1 INTEGER NOT NULL,
#    jump BIT NOT NULL,
#    PRIMARY KEY (piece, x0, y0, z0, x1, y1, z1)
#);
#''')

BOARD_LOWER_BOUNDS = 0
BOARD_UPPER_BOUNDS = 8
MOVE_TEMPLATE = {
                    'piece':'\0',
                    'x0':-1,
                    'y0':-1,
                    'z0':-1,
                    'x1':-1,
                    'y1':-1,
                    'z1':-1,
                    'jump':False,
                    'attacking_only':False,
            }

def create_move_entry(x0, y0, z0, x1, y1, z1, p, jump=False, attacking_only=False):
    move = copy(MOVE_TEMPLATE)

    move['piece'] = p
    move['x0'] = x0
    move['y0'] = y0
    move['z0'] = z0
    move['x1'] = x1
    move['y1'] = y1
    move['z1'] = z1
    move['jump'] = jump
    move['attacking_only'] = attacking_only

    return move

def check_in_bounds(x,y,z):
    return BOARD_LOWER_BOUNDS <= x < BOARD_UPPER_BOUNDS and BOARD_LOWER_BOUNDS <= y < BOARD_UPPER_BOUNDS and BOARD_LOWER_BOUNDS <= z < BOARD_UPPER_BOUNDS

def get_bishop_moves(x0,y0,z0,p, max_distance=BOARD_UPPER_BOUNDS-1):
    moves = []
    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0+c, y0+c, z0+c, p))

    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0+c, y0+c, z0-c, p))
    
    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0+c, y0-c, z0+c, p))
    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0+c, y0-c, z0-c, p))
    return moves

def get_priest_moves(x0,y0,z0,p, max_distance=BOARD_UPPER_BOUNDS-1):
    moves = []
    
    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0+c, y0+c, z0, p))

    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0, y0+c, z0+c, p))
    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0+c, y0, z0+c, p))

    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0+c, y0-c, z0, p))

    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0, y0+c, z0-c, p))
    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0+c, y0, z0-c, p))
    return moves

def get_rook_moves(x0,y0,z0,p, max_distance=BOARD_UPPER_BOUNDS-1):
    moves = []
    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0+c, y0, z0, p))

    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0, y0+c, z0, p))
        
    for c in range(-max_distance, max_distance+1):
        if c == 0:
            continue
        moves.append(create_move_entry(x0, y0, z0, x0, y0, z0+c, p))

    return moves

def get_paladin_moves(x0,y0,z0,p):
    moves=[] 

    moves.append(create_move_entry(x0, y0, z0, x0+2, y0+1, z0, p))

    moves.append(create_move_entry(x0, y0, z0, x0+2, y-1, z0, p))

    moves.append(create_move_entry(x0, y0, z0, x0+2, y0, z0+1, p))

    moves.append(create_move_entry(x0, y0, z0, x0+2, y0, z0-1, p))

    moves.append(create_move_entry(x0, y0, z0, x0, y0+2, z0+1, p))

    moves.append(create_move_entry(x0, y0, z0, x0, y0+2, z0-1, p))

    moves.append(create_move_entry(x0, y0, z0, x0, y0+1, z0+2, p))

    moves.append(create_move_entry(x0, y0, z0, x0, y0-1, z0+2, p))

    moves.append(create_move_entry(x0, y0, z0, x0+1, y0, z0+2, p))

    moves.append(create_move_entry(x0, y0, z0, x0-1, y0, z0+2, p))

    moves.append(create_move_entry(x0, y0, z0, x0+1, y0+2, z0, p))

    moves.append(create_move_entry(x0, y0, z0, x0-1, y0+2, z0, p))

    moves.append(create_move_entry(x0, y0, z0, x0-2, y0+1, z0, p))

    moves.append(create_move_entry(x0, y0, z0, x0-2, y-1, z0, p))

    moves.append(create_move_entry(x0, y0, z0, x0-2, y0, z0+1, p))

    moves.append(create_move_entry(x0, y0, z0, x0-2, y0, z0-1, p))

    moves.append(create_move_entry(x0, y0, z0, x0, y0-2, z0+1, p))

    moves.append(create_move_entry(x0, y0, z0, x0, y0-2, z0-1, p))

    moves.append(create_move_entry(x0, y0, z0, x0, y0+1, z0-2, p))

    moves.append(create_move_entry(x0, y0, z0, x0, y0-1, z0-2, p))

    moves.append(create_move_entry(x0, y0, z0, x0+1, y0, z0-2, p))

    moves.append(create_move_entry(x0, y0, z0, x0-1, y0, z0-2, p))

    moves.append(create_move_entry(x0, y0, z0, x0+1, y0-2, z0, p))

    moves.append(create_move_entry(x0, y0, z0, x0-1, y0-2, z0, p))
    
    for m in moves:
        m['jump'] = True

    return moves

def get_dragon_moves(x0,y0,z0,p):
    vectors = [[2, 2, 1],[2,1,2],[1,2,2]]
    moves=[]
    for s in vectors:
        moves.append(create_move_entry(x0,y0,z0,x0+s[0], y0+s[1], z0+s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0+s[0], y0+s[1], z0-s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0+s[0], y0-s[1], z0+s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0+s[0], y0-s[1], z0-s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0-s[0], y0+s[1], z0+s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0-s[0], y0+s[1], z0-s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0-s[0], y0-s[1], z0+s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0-s[0], y0-s[1], z0-s[2],p, jump=True))

    return moves

def get_knight_moves(x0,y0,z0,p):
    vectors = [[1, 1, 2],[1,2,1],[2,1,1]]
    moves=[]
    for s in vectors:
        moves.append(create_move_entry(x0,y0,z0,x0+s[0], y0+s[1], z0+s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0+s[0], y0+s[1], z0-s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0+s[0], y0-s[1], z0+s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0+s[0], y0-s[1], z0-s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0-s[0], y0+s[1], z0+s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0-s[0], y0+s[1], z0-s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0-s[0], y0-s[1], z0+s[2],p, jump=True))
        moves.append(create_move_entry(x0,y0,z0,x0-s[0], y0-s[1], z0-s[2],p, jump=True))

    return moves

def get_king_moves(x0,y0,z0,p):
    moves = []
    moves.extend(get_rook_moves(x0,y0,z0,p,max_distance=1))
    moves.extend(get_priest_moves(x0,y0,z0,p,max_distance=1))
    moves.extend(get_bishop_moves(x0,y0,z0,p,max_distance=1))
    return moves

def get_pawn_moves(x0, y0, z0, is_white=True):
    moves=[]
    p='i' if is_white else 'I'
    adder = 1 if is_white else -1
    moves.append(create_move_entry(x0,y0,z0,x0+adder,y0,z0,p))
    if (is_white and x0 == 1) or (not is_white and x0==6):
        moves.append(create_move_entry(x0,y0,z0,x0+2*adder,y0,z0,p))
    
    
    moves.append(create_move_entry(x0,y0,z0,x0+adder,y0,z0+1,p,attacking_only=True))
    moves.append(create_move_entry(x0,y0,z0,x0+adder,y0+1,z0,p,attacking_only=True))
    moves.append(create_move_entry(x0,y0,z0,x0+adder,y0+1,z0+1,p,attacking_only=True))
    moves.append(create_move_entry(x0,y0,z0,x0+adder,y0,z0-1,p,attacking_only=True))
    moves.append(create_move_entry(x0,y0,z0,x0+adder,y0-1,z0,p,attacking_only=True))
    moves.append(create_move_entry(x0,y0,z0,x0+adder,y0-1,z0-1,p,attacking_only=True))
    moves.append(create_move_entry(x0,y0,z0,x0+adder,y0+1,z0-1,p,attacking_only=True))
    moves.append(create_move_entry(x0,y0,z0,x0+adder,y0-1,z0+1,p,attacking_only=True))
    return moves
def handle_piece_with_starting_position(x0,y0,z0,p):
    move_entries = []
    if p.lower() in 'rqgu':
        move_entries.extend(get_rook_moves(x0,y0,z0,p))
    if p.lower() in 'bqwu':
        move_entries.extend(get_bishop_moves(x0,y0,z0,p))
    if p.lower() in 'tqgw':
        move_entries.extend(get_priest_moves(x0,y0,z0,p))

    if p.lower() == 'p':
        move_entries.extend(get_paladin_moves(x0,y0,z0,p))
    elif p.lower() == 'd':
        move_entries.extend(get_dragon_moves(x0,y0,z0,p))
    elif p.lower() == 'n':
        move_entries.extend(get_knight_moves(x0,y0,z0,p))
    elif p.lower() == 'k':
        move_entries.extend(get_king_moves(x0,y0,z0,p))
    elif p == 'i':
        move_entries.extend(get_pawn_moves(x0,y0,z0))
    elif p == 'I':
        move_entries.extend(get_pawn_moves(x0,y0,z0,is_white=False))

    return move_entries

db_folder = './db/'
db_name = '3DChess.db'
db_loc = f'../{db_folder}/{db_name}'

db = sqlite_utils.Database(db_loc, recreate=True)

db['moves'].create(
        {
            'piece':str,
            'x0':int,
            'y0':int,
            'z0':int,
            'x1':int,
            'y1':int,
            'z1':int,
            'jump':bool,
            'attacking_only': bool,
        },
        pk=('piece', 'x0', 'y0', 'z0', 'x1', 'y1', 'z1'),
        strict=True
    )

pieces = 'rtbpdnkqigwu'
pieces += pieces.upper()

for p in tqdm(pieces):
    for x in range(BOARD_UPPER_BOUNDS):
        for y in range(BOARD_UPPER_BOUNDS):
            for z in range(BOARD_UPPER_BOUNDS):
                candidate_moves=handle_piece_with_starting_position(x,y,z,p)
                moves =[]
                for m in candidate_moves:
                    if check_in_bounds(m['x1'],m['y1'],m['z1']):
                        moves.append(m)
                db['moves'].insert_all(moves)
