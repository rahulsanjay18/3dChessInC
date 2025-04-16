# Some Documentation

## Classes
Coordinates:
    - Contains:
        - x
        - y
        - z

Board
- Contains:
    - Piece it is representing
    - Array of bits where bit is 1 if piece is present there
- Functions:
    - set: set the bit at the coordinates to high
        - input: coordinates
        - output: void
    - unset: set the bit at the coordinates to low
        - input: coordinates
        - output: void
    - \_convert\_to\_board\_coords: convert xyz coords to the position on the board
        - input: coordinates
        - output: location of the bit on the board
        - might not be needed.
    - get: get value at bit position xyz
        - input: coordinates
        - output: bit or bool

Board Group:
- Contains:
    - array of boards
    - mapping from int to char
        - how to sync with game state?
- Functions:
    - idk

Game State:
- Contains:
    - Group of boards for all Pieces
    - Captured piece counter
    - turn
    - Castle status
    - Move history
    - Pawn 1st move status
        - maybe not needed
    - mapping for number to piece
    - Checkmate or not.
- Functions:
    - board\_representation: get an array of chars containing the board state
        - output: 8x8x8 array of chars
    - pretty\_print\_board: add nice formatting to board
        - output: really long string
    - get\_turn: get whose turn it is.
    - get\_piece: get the piece at the location.
        - input: coordinates
        - output: piece (as an int, NOT a char)
    - convert\_piece\_to\_char: turn piece number to char
        - input: number
        - output: char
        - might not be needed
    - is\_checkmate:
        - Checks if we're in checkmate
    - save: Save to a file
        - filepath
    - load: Load to file
        - need to check if the file is valid, but that might be a later thing.
SQL Communicator:
    - Contains:
        - db path
    - Functions:
        - check\_move\_valid: checks if the move is valid
            - input: piece, xyz, new\_xyz
            - output: bool
        - get\_valid\_moves: return a list of valid move coordinates
            - input: piece, xyz, attacking
            - outputs: list[coordinates]
        - log\_move

Game:
    - Contains:
        - Game state
        - Start Move
        - End Move
    - Functions:
        - Initialize game
            - Create a new game state
        - move: Moves piece
            - Input: xyz, to xyz
            - Output: Success or not.
        - game\_loop:
            1. Initialize board
            2. begin game loop
            3. wait for move
            4. Make move.
            5. if move succeeds, stuff should be updated in the game state. if not, nothing changes
            6. nullify move vars

Game "GUI"
    Contains:
        - Game
    Functions:
        - send\_move: Send the move to the game
        - get\_board
        
