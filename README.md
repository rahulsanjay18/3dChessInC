# CubeChess in C
## Purpose
This is similar to my other project that I started in 2021 which was doing this in python, but I realized that there were generally better ways I could go about representing the board, checking if a piece is already there, etc. I missed coding in C, so this was a good excuse to change the language as well.

This is my version of 3D Chess. It is not the same as the 4x4x4 stuff I'd seen on sale on Amazon, but rather a new game that tries to generalize the game of chess to 3D. This involves creating new pieces that take advantage of the newly added dimension, and the movements that you can do with them. In fact, I think there are more new pieces than there are old ones. For what it's worth, I have no knowledge of anyone else doing this, but if someone has, please let me know because I'd love to see how others tackle this.

## The General Idea
Picture a cube that is made up of smaller cubes (side length: 1 unit), such that the length, width and height of the big cube is 8 units long. We call this an 8x8x8 lattice, or, our game board.

The pieces, therefore, have 3 different directions they can theoretically move in, the x direction, the y direction, and the z direction.

![](imgs/cube6274282860234311237.png)

Generalizing the pieces in traditional chess to 3D requires a slightly different view of how pieces move.
Generally, pieces in 2D chess move in three different ways:
- Straight (Rook, Bishop, Queen, King)
- L shaped (Knight)
- Straight but Diagonal Attack (Pawn)

We know that pieces like the King and Pawn have special limitations on their movement, and they also have the ability to do fancy things like castling and en-passant, and that pawn thing where the first move can be 2 squares, but bear with me here, as generalizing these to 3D still allows us to preserve these special cases, with the slight caveat that with castling, as there's some board logistics that I haven't quite figured out.

![s-l1200.webp](imgs/s-l1200.webp)

We can think of these three different movements as "passing through" various parts of the square they occupy, so, rather than describing them as I did above, we can reframe the movements like so:
- Passing through the edge (either x or y direction) (Rook, Queen, King, Pawn)
- Passing through the corner (xy direction) (Queen, King, Pawn (when attacking))
- Passing through one edge, and one corner in the direction of the edge passed (x direction twice, y direction once) (Knight)

The 3D generalization of a square is a cube. Cubes have three parts:
- Face (6)
- Edge (12)
- Vertices (8)

So, our pieces in 3D chess should be able to move through each of these parts of a cube.

## Board Setup
For the sake of simplicity, I will be using (x,y,z) notation to describe piece movements. I do think it would be better to have a kind of algebraic notation, and I have some ideas for that, but for now, it is easier to communicate in x,y, z.

Here are the meanings of each direction, using books lined up on a bookshelf:

![](imgs/books_lined_up.jpg)

The X direction is the "layer" of the board we are in.  Each unit in the x direction is like moving to the next book in line.
The Z direction is moving in the direction of the length of the spine of the book.
The Y direction is  moving perpendicular to the spine of the book, while remaining on the same book

The picture of the cube above is consistent with these directons, but it was only one cube, so I figured the book analogy would be more helpful.

## Pieces
Now, we generalize the pieces, using the scheme I outlined above, while keeping in mind how our 2D chess game works.
Note, c ∈ [1, 7]

|Name     |Colloquial Name|Movement Vector                                                                                                                                                                    |Attack Vector            |Character Representation (white, black)|
|---------|---------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------|---------------------------------------|
|FRook    |Rook           |<X±c,0,0>, <0,Y±c,0>, <0,0,Z±c>                                                                                                                                                    |Same as Movement         |r, R                                   |
|ERook    |Priest         |<X±c,Y±c,0>, <0,Y±c,Z±c>, <X±c,0,Z±c>, <X±c,Y∓c,0>, <0,Y±c,Z∓c>, <X±c,0,Z∓c>                                                                                                       |Same as Movement         |t, T                                   |
|VRook    |Bishop         |<X±c,Y±c,Z±c>, <X±c,Y±c,Z∓c>, <X±c,Y∓c,Z±c>,  <X±c,Y∓c,Z∓c>                                                                                                                        |Same as Movement         |b, B                                   |
|FEKnight |Paladin        |<X+2,Y±1,0>, <X+2,0,Z±1>, <X-2,Y±1,0>, <X-2,0,Z±1>, <X±1,Y+2,0>, <0,Y+2,Z±1>, <X±1,Y-2,0>, <0,Y-2,Z±1>, <0,Y±1,Z+2>, <X±1,0,Z+2>, <0,Y±1,Z-2>, <X±1,0,Z-2>                         |Same as Movement         |p, P                                   |
|EVKnight |Dragon         |<X±2,Y±2,Z±1>, <X±2,Y±2,Z∓1>, <X±2,Y±1,Z±2>, <X±2,Y∓1,Z±2>, <X±1,Y±2,Z±2>, <X∓1,Y±2,Z±2>, <X±2,Y∓2,Z±1>, <X±2,Y∓2,Z∓1>, <X∓2,Y±1,Z±2>, <X∓2,Y∓1,Z±2>, <X±1,Y±2,Z∓2>, <X∓1,Y±2,Z∓2> |Same as Movement         |d, D                                   |
|FVKnight |Knight         |<X+2,Y±1,Z±1>, <X+2,Y±1,Z∓1>, <X-2,Y±1,Z±1>, <X-2,Y±1,Z∓1>, <X±1,Y+2,Z±1>, <X±1,Y+2,Z∓1>, <X±1,Y-2,Z±1>, <X±1,Y-2,Z∓1>, <X±1,Y±1,Z+2>, <X±1,Y∓1,Z+2>, <X±1,Y±1,Z-2>, <X±1,Y∓1,Z-2> |Same as Movement         |n, N                                   |
|King     |King           |Combine Rook, Priest, and Bishop, set c=1                                                                                                                                          |Same as Movement         |k, K                                   |
|Queen    |Queen          |Combine Rook, Priest, and Bishop but you can only pick one direction                                                                                                               |Same as Movement         |q, Q                                   |
|Pawn     |Pawn           |Rook, with c=2 on first move, c=1 otherwise                                                                                                                                        |Priest & Bishop, with c=1 & only in the "forward" direction|i, I                                   |
|FEAdvisor|General        |Combine Rook and Priest but you can only pick one direction                                                                                                                        |Same as Movement         |g, G                                   |
|EVAdvisor|Wizard         |Combine Priest and Bishop but you can only pick one direction                                                                                                                      |Same as Movement         |w, W                                   |
|FVAdvisor|Duke           |Combine Rook and Bishop but you can only pick one direction                                                                                                                        |Same as Movement         |u, U                                   |

## Initial Board
### Some notes on board setup
We want to mimic the "intent" of the initial 2D chess board setup. The following conclusions I've come to about the inital board setup of 2D chess are a little circular.
The game is old, and I don't know if the original creators set up the board with the relative values of each piece in mind. I'll use this idea, and my personal hunches as to why the
pieces are places where they are to derive a set of rules.
Let's look at what the original 2d chess board looks like:

|zy>|a  |b  |c  |d  |e  |f  |g  |h  |<yz|
|---|---|---|---|---|---|---|---|---|---|
|8  |R  |N  |B  |Q  |K  |B  |N  |R  |8  |
|7  |I  |I  |I  |I  |I  |I  |I  |I  |7  |
|6  |x  |x  |x  |x  |x  |x  |x  |x  |6  |
|5  |x  |x  |x  |x  |x  |x  |x  |x  |5  |
|4  |x  |x  |x  |x  |x  |x  |x  |x  |4  |
|3  |x  |x  |x  |x  |x  |x  |x  |x  |3  |
|2  |i  |i  |i  |i  |i  |i  |i  |i  |2  |
|1  |r  |n  |b  |q  |k  |b  |n  |r  |1  |
|zy>|a  |b  |c  |d  |e  |f  |g  |h  |<yz|

- The most valuable piece (the king) is on the outer edge (top and bottom), and around the middle.
- the second most valuable piece (the queen), is next to the king, protecting it.
- The third most powerful piece (the rook), is on the corners of the board.
- The bishops are positioned such that the spaces immediately in front of the king and queen are covered by the bishop
- The knights are positioned with the same intent, they cover the same squares.
- The pawns offer a layer of protection for all of the other "important" pieces
- The bishops' paths also happen to be able to cover the entire board, with each bishop being able to reach all the squares that have the same color as their original square
- the board is symmetrical in the first three and last three columns.

So, from here, we're going to come up with some rules for our piece placement, and do our best to ensure that each of our 3D pieces conforms with this intent.
- The queens and the king must be in the center four squares
- The Priests, Bishop, Paladin, Knight, and Dragon should be able to reach the same yz position that the king and queens occupy but one layer ahead of them
- The number of Priests and Bishops must **at least** be able to reach the entire board. This rule combines the reach of pieces of the same type
- Similar thing with the Paladin, Knight, Dragon, and Rook, though they might already be able to do it on their own (need to calculate that). In that case, 4-ish would be a good idea.
- The 2nd and 7th layer is just a layer of pawns. Personally I think this is kind of boring, but for now it is okay, and still does conform to what 2D chess does.
- The "Advisors" shall occupy the four corners of the first layer and last layer. Their order of arrangement is still TBD, but I'd want it to be hard for them to get out, much like the Rook in 2D chess.
-  Try to preserve symmetry radially outward from the center four squares on the first and last layer. this is not important, but a nice-to-have.

### The Initial Board
Layer 1 (x=0):

|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|
|---|---|---|---|---|---|---|---|---|---|
|7  |g  |w  |p  |r  |r  |b  |u  |g  |7  |
|6  |u  |d  |d  |n  |p  |n  |d  |w  |6  |
|5  |b  |n  |b  |t  |t  |b  |d  |p  |5  |
|4  |r  |p  |t  |q  |q  |t  |n  |r  |4  |
|3  |r  |n  |t  |q  |k  |t  |p  |r  |3  |
|2  |p  |d  |b  |t  |t  |b  |n  |b  |2  |
|1  |w  |d  |n  |p  |n  |d  |d  |u  |1  |
|0  |g  |u  |b  |r  |r  |p  |w  |g  |0  |
|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|

Layer 2 (x=1):

|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|
|---|---|---|---|---|---|---|---|---|---|
|7  |i  |i  |i  |i  |i  |i  |i  |i  |7  |
|6  |i  |i  |i  |i  |i  |i  |i  |i  |6  |
|5  |i  |i  |i  |i  |i  |i  |i  |i  |5  |
|4  |i  |i  |i  |i  |i  |i  |i  |i  |4  |
|3  |i  |i  |i  |i  |i  |i  |i  |i  |3  |
|2  |i  |i  |i  |i  |i  |i  |i  |i  |2  |
|1  |i  |i  |i  |i  |i  |i  |i  |i  |1  |
|0  |i  |i  |i  |i  |i  |i  |i  |i  |0  |
|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|

Layer 3 (x=2):

|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|
|---|---|---|---|---|---|---|---|---|---|
|7  |x  |x  |x  |x  |x  |x  |x  |x  |7  |
|6  |x  |x  |x  |x  |x  |x  |x  |x  |6  |
|5  |x  |x  |x  |x  |x  |x  |x  |x  |5  |
|4  |x  |x  |x  |x  |x  |x  |x  |x  |4  |
|3  |x  |x  |x  |x  |x  |x  |x  |x  |3  |
|2  |x  |x  |x  |x  |x  |x  |x  |x  |2  |
|1  |x  |x  |x  |x  |x  |x  |x  |x  |1  |
|0  |x  |x  |x  |x  |x  |x  |x  |x  |0  |
|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|

Layer 4 (x=3):

|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|
|---|---|---|---|---|---|---|---|---|---|
|7  |x  |x  |x  |x  |x  |x  |x  |x  |7  |
|6  |x  |x  |x  |x  |x  |x  |x  |x  |6  |
|5  |x  |x  |x  |x  |x  |x  |x  |x  |5  |
|4  |x  |x  |x  |x  |x  |x  |x  |x  |4  |
|3  |x  |x  |x  |x  |x  |x  |x  |x  |3  |
|2  |x  |x  |x  |x  |x  |x  |x  |x  |2  |
|1  |x  |x  |x  |x  |x  |x  |x  |x  |1  |
|0  |x  |x  |x  |x  |x  |x  |x  |x  |0  |
|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|

Layer 5 (x=4):

|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|
|---|---|---|---|---|---|---|---|---|---|
|7  |x  |x  |x  |x  |x  |x  |x  |x  |7  |
|6  |x  |x  |x  |x  |x  |x  |x  |x  |6  |
|5  |x  |x  |x  |x  |x  |x  |x  |x  |5  |
|4  |x  |x  |x  |x  |x  |x  |x  |x  |4  |
|3  |x  |x  |x  |x  |x  |x  |x  |x  |3  |
|2  |x  |x  |x  |x  |x  |x  |x  |x  |2  |
|1  |x  |x  |x  |x  |x  |x  |x  |x  |1  |
|0  |x  |x  |x  |x  |x  |x  |x  |x  |0  |
|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|

Layer 6 (x=5):

|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|
|---|---|---|---|---|---|---|---|---|---|
|7  |x  |x  |x  |x  |x  |x  |x  |x  |7  |
|6  |x  |x  |x  |x  |x  |x  |x  |x  |6  |
|5  |x  |x  |x  |x  |x  |x  |x  |x  |5  |
|4  |x  |x  |x  |x  |x  |x  |x  |x  |4  |
|3  |x  |x  |x  |x  |x  |x  |x  |x  |3  |
|2  |x  |x  |x  |x  |x  |x  |x  |x  |2  |
|1  |x  |x  |x  |x  |x  |x  |x  |x  |1  |
|0  |x  |x  |x  |x  |x  |x  |x  |x  |0  |
|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|

Layer 7 (x=6):

|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|
|---|---|---|---|---|---|---|---|---|---|
|7  |I  |I  |I  |I  |I  |I  |I  |I  |7  |
|6  |I  |I  |I  |I  |I  |I  |I  |I  |6  |
|5  |I  |I  |I  |I  |I  |I  |I  |I  |5  |
|4  |I  |I  |I  |I  |I  |I  |I  |I  |4  |
|3  |I  |I  |I  |I  |I  |I  |I  |I  |3  |
|2  |I  |I  |I  |I  |I  |I  |I  |I  |2  |
|1  |I  |I  |I  |I  |I  |I  |I  |I  |1  |
|0  |I  |I  |I  |I  |I  |I  |I  |I  |0  |
|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|

Layer 8 (x=7):

|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|
|---|---|---|---|---|---|---|---|---|---|
|7  |G  |W  |P  |R  |R  |B  |U  |G  |7  |
|6  |U  |D  |D  |N  |P  |N  |D  |W  |6  |
|5  |B  |N  |B  |T  |T  |B  |D  |P  |5  |
|4  |R  |P  |T  |Q  |Q  |T  |N  |R  |4  |
|3  |R  |N  |T  |Q  |K  |T  |P  |R  |3  |
|2  |P  |D  |B  |T  |T  |B  |N  |B  |2  |
|1  |W  |D  |N  |P  |N  |D  |D  |U  |1  |
|0  |G  |U  |B  |R  |R  |P  |W  |G  |0  |
|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|

### Explanation
final board setup is TBD, and prone to change. its a hard problem. following the center-covering principle, each piece type covers the center 4 at least once. Specifically,
- Paladins: 1
- Knights: 2
- Dragons: 3
- Bishops: 1
- Priests: 2

I'm fairly confident that Priests can only cover one center square at a time. Figured theyd be more useful in the center. Bishops have the same problem, but this arrangement is a little more symmetrical, and I like it better. That means that the center squares are covered 9 times each.

Still need to calculate the "reachability" of each of the pieces. I used to have the calculations and then I lost it.

## Appendix
Board template:

|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|
|---|---|---|---|---|---|---|---|---|---|
|7  |x  |x  |x  |x  |x  |x  |x  |x  |7  |
|6  |x  |x  |x  |x  |x  |x  |x  |x  |6  |
|5  |x  |x  |x  |x  |x  |x  |x  |x  |5  |
|4  |x  |x  |x  |x  |x  |x  |x  |x  |4  |
|3  |x  |x  |x  |x  |x  |x  |x  |x  |3  |
|2  |x  |x  |x  |x  |x  |x  |x  |x  |2  |
|1  |x  |x  |x  |x  |x  |x  |x  |x  |1  |
|0  |x  |x  |x  |x  |x  |x  |x  |x  |0  |
|zy>|0  |1  |2  |3  |4  |5  |6  |7  |<yz|
