import sqlite3
import sqlite_utils

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

db_folder = './db/'
db_name = '3DChess.db'
db_loc = f'{db_folder}/{db_name}'

db = sqlite_utils.Database(db_loc)

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
        },
        pk=(piece, x0, y0, z0, x1, y1, z1),
        strict=True
    )

pieces = 'rtbpdnkqigwu'
pieces += pieces.upper()


