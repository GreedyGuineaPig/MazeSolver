/*
*  maze.h
*  maze header file for Lab 6
*
*  Barb Wahl, Theresa Wilson, and Haris Skiadas
*  Revised 3-27-20
*
*  DO NOT CHANGE THIS FILE
*
*  General information about the maze class and how it will be used:
*     A maze is represented by a 2-dimensional dynamic array of squares. Each
*     maze has exactly one start square and one exit square. Some mazes are
*     impossible to solve (no solution path); some have a unique solution path;
*     and some have two or more solution paths.
*
*     The smallest possible mazes have just two squares.  The size of the
*     largest maze is constrained only by available memory.
*
*  The maze constructor:
*
*     A maze is constructed from a file input stream of the following format:
*       - The tokens are separated by any kind of whitespace characters
*         (spaces, tabs, newlines, etc.), and the final token is followed
*         by whitespace.
*
*       - The first token is a positive integer representing the number of
*         rows R in the maze.
*
*       - The second token is a positive integer representing the number of
*         columns C in the maze.
*
*       - The remaining R*C tokens are symbols (chars) representing the squares
*         in the maze. The first C values correspond to the top row of the maze,
*         left to right, the next C values correspond to the second row, and so on.
*
*       - The different symbols represent different kinds of squares:
*
*              # => WALL square
*              S => START square
*              E => EXIT square
*              - => PLAIN square
*
*         (Refer to square.h for full documentation of the square class.)
*
*       - EXAMPLE:  If the stream contents are as follows:
*
*              3 4   - - -   - S    #  \n # - # E \t - -   \n
*
*         then the maze will have 3 rows, 4 columns, and will look as follows
*         when printed:
*              - - - -
*              S # # -
*              # E - -
*
*  INSTANCE VARIABLES
*     square** squares;   // pointer to a 2-dimensional dynamic array of squares
*     int numRows;        // number of rows in the maze
*     int numCols;        // number of columns in the maze
*     square* start_ptr;  // pointer to the start square
*     square* exit_ptr;   // pointer to the exit square
*
*  Copy Constructor:  disabled
*  Assignment Operator:  disabled
*/

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>

#include "square.h"

namespace mazelab
{
class maze
{
  public:
    //
    //  constructor -- initializes a maze from an input stream
    //  Parameter: `in` is a stream of whitespace-separated tokens; there
    //     is at least one whitespace character after the last token.
    //  Precondition:  The first two tokens of `in` are positive integers that
    //     represent the number of rows (R) and columns (C) in the maze.
    //  Precondition:  The next R*C tokens of `in` are characters representing
    //     the squares in the maze.
    //  Precondition:  There is exactly one start square and one exit square.
    //  Postcondition: `squares` points to the R x C array of maze squares.
    //  Postcondition: `numRows` and `numCols` have been properly initialized.
    //  Postcondition: `start_ptr` points to the start square and `exit_ptr` points
    //     to the exit square.
    //  Exception: Throws domain_error if there is an error in the format of
    //     the maze being read from the input stream.
    //  Exception: Throws domain_error if any of the preconditions are violated.
    //
    explicit maze(std::istream& in);

    //
    // Destructor
    //
    ~maze();

    //
    // getNumRows
    //  Postcondition:  Return value is the number of rows in the maze.
    //
    int getNumRows() const;

    //
    // getNumCols
    //  Postcondition:  Return value is the number of columns in the maze.
    //
    int getNumCols() const;

    //
    // getStart
    //  Postcondition:  Return value is a pointer to the start
    //     square of the maze.
    //
    square* getStart() const;

    //
    // getExit
    //  Postcondition:  Return value is a pointer to the exit
    //     square of the maze.
    //
    square* getExit() const;

    //
    // get -- get a pointer to a square by row and column indices
    //  Precondition:  `i` is in range 0 through numRows - 1.
    //  Precondition:  `j` is in range 0 through numCols - 1.
    //  Postcondition:  Return value is a pointer to the square in
    //     row i and column j of this maze.
    //  Exception: Throws out_of_range if `i` is invalid.
    //  Exception: Throws out_of_range if `j` is invalid.
    //
    square* get(int i, int j) const;

    //
    // getNeighbors
    //  Precondition: `sq_ptr` is a pointer to a square in this maze.
    //  Postcondition: Return value is a vector of pointers to the NON-WALL
    //     squares in this maze that are neighbors of the square pointed to by
    //     `sq_ptr`, where the vector is filled in this order: North (up one),
    //     East (right one), South (down one) and West (left one).
    //  Note: Corner squares have at most two neighbors, and side squares have
    //     at most three neighbors.
    //  Note: If `sq_ptr` has no non-WALL neighbor squares, the return value is
    //     an empty vector.
    //
    //  EXAMPLE: In the maze below:
    //     - - - -
    //     S # # -
    //     # E - -
    //
    //     If sq_ptr points to the square at (0, 1) then the return value will
    //     be a vector of length 2 storing, in this order:
    //        - a pointer to the (0, 2) square
    //        - a pointer to the (0, 0) square
    //
    std::vector<square*> getNeighbors(const square* sq_ptr) const;

  private:
    square** squares;   // pointer to a 2-dimensional dynamic array of squares
    int numRows;        // number of rows in the maze
    int numCols;        // number of columns in the maze
    square* start_ptr;  // pointer to the start square
    square* exit_ptr;   // pointer to the exit square

    // disabled copy constructor (not needed, DON'T implement!)
    maze(const maze& other);

    // disabled assignment operator (not needed, DON'T implement!)
    maze& operator=(const maze& other);
};

//
// output stream operator
//  Postcondition: A representation of this maze based on square kind
//     symbols and square status symbols is put into `out`.
//  Postcondition:  The output stream `out` is returned to allow for
//     chaining of output.
//
//  Output format: First a newline character ('\n'), then each square
//     is output followed by a single space, with a 'n' at then end of
//     each row.  HINT: See the stream output operator for the square
//     class for the symbol that should be output for each kind of square.
//     the square
//
//  EXAMPLE:  Maze with 3 rows, 4 columns, and the following squares:
//     START at [1,0]; EXIT at [2,1]; WALLs at [1,1] [1,2] [2,0]; all
//     the rest are PLAIN UNVISITED squares, with the exception of
//     [0,0] and [0,1], which are PLAIN EXPLORED squares, and [0,2],
//     which is a PLAIN square on the WORKLIST.
//
//     The output for this maze would look as follows:
//         . . @ -
//         S # # -
//         # E - -
//
std::ostream& operator<<(std::ostream& out, const maze& maze);

}  // namespace mazelab

#endif /* MAZE_H */
