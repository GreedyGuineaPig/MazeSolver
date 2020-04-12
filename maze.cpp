// maze.cpp -- Implementation of Maze Class
// CS 223, Lab 6
//
// Name: Hiroki Nakano
// Date: 11/4/2020

/*
*  INSTANCE VARIABLES
*     square** grid;     // pointer to a 2-dimensional dynamic array of squares
*     int numRows;       // number of rows in the maze
*     int numCols;       // number of columns in the maze
*     square* start_ptr; // pointer to the start square
*     square* exit_ptr;  // pointer to the exit square
*
*  CLASS INVARIANTS
*     1. grid[i][j] is the maze square in ROW i and COLUMN j.
*     2. Each maze has exactly one START square and one EXIT square.
*/

#include "maze.h"

#include <sstream>    // provides stringstreams
#include <stdexcept>  // provides standard exceptions

using namespace std;

namespace mazelab
{
//
//  constructor -- initializes a maze from an input stream
//  Parameter: `in` is a stream of whitespace-separated tokens; there
//     is at least one whitespace character after the last token.
//  Precondition:  The first two tokens of `in` are positive integers that
//     represent the number of rows (R) and columns (C) in the maze.
//  Precondition:  The next R*C tokens of `in` are characters representing
//     the squares in the maze.
//  Precondition:  There is exactly one start square and one exit square.
//  Postcondition: `grid` points to the R x C array of maze squares.
//  Postcondition: `numRows` and `numCols` have been properly initialized.
//  Postcondition: `start_ptr` points to the start square and `exit_ptr` points
//     to the exit square.
//  Exception: Throws domain_error if there is an error in the format of
//     the maze being read from the input stream.
//  Exception: Throws domain_error if any of the preconditions are violated.
//
maze::maze(istream& in)
{
    //initialize variables
    in >> numRows >> numCols;
    squares = new square*[numRows];
    for (int r = 0; r < numRows; r++)
    {
        squares[r] = new square[numCols];
    }
    start_ptr = NULL;
    exit_ptr = NULL;

    //store each status
    char sq_kind;
    for (int r = 0; r < numRows; r++)
    {
        for (int c = 0; c < numCols; c++)
        {
            in >> sq_kind;
            // cout << "kind is space ? " << (sq_kind == ' ') << endl;
            // cout << "********" << r << ":" << c << " " << sq_kind << endl;
            squares[r][c] = square(sq_kind, r, c);
            //start check
            if (sq_kind == 'S')
            {
                if (start_ptr != NULL)
                {
                    throw domain_error("start squares should be only one.");
                }
                else
                {
                    start_ptr = &squares[r][c];
                }
            }
            //exit check
            if (sq_kind == 'E')
            {
                if (exit_ptr != NULL)
                {
                    throw domain_error("start squares should be only one.");
                }
                else
                {
                    exit_ptr = &squares[r][c];
                }
            }
        }
    }
    //start, exit is available
    if (start_ptr == NULL || exit_ptr == NULL)
    {
        throw domain_error("start or exit is not available");
    }
}

//
// Destructor
//
maze::~maze()
{
    for (int r = 0; r < numRows; r++)
    {
        delete squares[r];
    }
    delete squares;
    squares = NULL;
    start_ptr = NULL;
    exit_ptr = NULL;
}

//
// getNumRows
//  Postcondition:  Return value is the number of rows in the maze.
//
int maze::getNumRows() const
{
   return numRows;
}

//
// getNumCols
//  Postcondition:  Return value is the number of columns in the maze.
//
int maze::getNumCols() const
{
   return numCols;
}

//
// getStart
//  Postcondition:  Return value is a pointer to the start
//     square of the maze.
//
square* maze::getStart() const
{
   return start_ptr;
}

//
// getExit
//  Postcondition:  Return value is a pointer to the exit
//     square of the maze.
//
square* maze::getExit() const
{
   return exit_ptr;
}

//
// get -- get a pointer to a square by row and column indices
//  Precondition:  `i` is in range 0 through numRows - 1.
//  Precondition:  `j` is in range 0 through numCols - 1.
//  Postcondition:  Return value is a pointer to the square in
//     row i and column j of this maze.
//  Exception: Throws out_of_range if `i` is invalid.
//  Exception: Throws out_of_range if `j` is invalid.
//
square* maze::get(int i, int j) const
{
    if (i < 0 || numRows - 1 < i || j < 0 || numCols - 1 < j)
    {
        throw out_of_range("i or j is invalid.");
    }
    else
    {
        return &squares[i][j];
    }
}

//
// getNeighbors
//  Precondition: `sq_ptr` is a pointer to a square in this maze.
//  Postcondition: Return value is a vector of pointers to the NON-WALL
//     squares in this maze that are neighbors of the square pointed to by
//     `sq_ptr`, where the vector is filled in this order: North (up one),
//     East (right one), South (down one) and West (left one).
//  Note: Corner squares have at most two neighbors, and side grid have
//     at most three neighbors.
//  Note: If `sq_ptr` has no non-WALL neighbor squares, the return value is
//     an empty vector.
//
// EXAMPLE: In the maze below:
//    - - - -
//    S # # -
//    # E - -
//
//    If sq_ptr points to the square at (0, 1) then the return value will
//    be a vector of length 2 storing, in this order:
//       - a pointer to the (0, 2) square
//       - a pointer to the (0, 0) square
//
vector<square*> maze::getNeighbors(const square* sq_ptr) const
{
   vector<square*> v;
   string str_position;
   str_position = sq_ptr -> getPosition();
   // cout << "***str_position: " << str_position << endl;
   int row, col;
   stringstream ss;
   ss << str_position;
   ss.ignore();
   ss >> row;
   ss.ignore();
   ss >> col;
   char sq_kind;
   // cout << "row: " << row << " col: " << col << endl;
   square* coordinate = NULL;
   for (int i = 0; i < 4; i++)
   {
    switch(i)
    {
        case 0:
            try
            {
                coordinate = get(row - 1, col);
            }
            catch (out_of_range& e)
            {
                break;
            }
            sq_kind = coordinate -> getKind();
            if (sq_kind != '#')
            {
                v.push_back(coordinate);
            }
            break;
        case 1:
            try
            {
                coordinate = get(row, col + 1);
            }
            catch (out_of_range& e)
            {
                break;
            }
            sq_kind = coordinate -> getKind();
            if (sq_kind != '#')
            {
                v.push_back(coordinate);
            }
            break;
        case 2:
            try
            {
                coordinate = get(row + 1, col);
            }
            catch (out_of_range& e)
            {
                break;
            }
            sq_kind = coordinate -> getKind();
            if (sq_kind != '#')
            {
                v.push_back(coordinate);
            }
            break;
        case 3:
            try
            {
                coordinate = get(row, col - 1);
            }
            catch (out_of_range& e)
            {
                break;
            }
            sq_kind = coordinate -> getKind();
            if (sq_kind != '#')
            {
                v.push_back(coordinate);
            }
            break;

    }
   }
   return v;
}

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
ostream& operator<<(std::ostream& out, const maze& maze)
{
    int row, col;
    row = maze.getNumRows();
    col = maze.getNumCols();
    out << "\n";
    square* ptr;
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            ptr = maze.get(r, c);
            out << *ptr << " ";
        }
        out << "\n";
    }
    return out;
}
}  // namespace mazelab
