/*
*  square.h
*  square header file for Lab 6
*
*  Barb Wahl, Theresa Wilson, and Haris Skiadas
*  Revised 3-26-20
*
*  DO NOT CHANGE THIS FILE
*
*  An instance of the square class represents a single square in the maze.
*
*  The five instance variables of a square are as follows:
*     - char `kind`: The kind of square this is; possible values:
*           '#' -- WALL
*           'S' -- START
*           'E' -- EXIT
*           '-' -- PLAIN
*
*     - char `status`: The status of the square with respect to being visited; 
*       possible values:
*           '-' -- UNVISITED
*           '@' -- WORKLIST
*           '.' -- EXPLORED
*           'X' -- SOLUTION
* 
*       Note: the same character is used for square kind PLAIN and square 
*             status UNVISITED. 
*
*     - int `row`: The row in which the square resides in the maze.
*       Row 0 is the top row.
*
*     - int `col`: The column in which the square resides in the maze.
*       Column 0 is the leftmost column.
*
*     - square* `prev`: Answers the question, "Which square was being explored
*       when the current square was added to the worklist?"  The previous
*       pointers can be followed from current square back to the start to
*       construct the path used to find the current square. If the current
*       square *is* the start square, prev will be NULL. By default, `prev`
*       is NULL when a square is created.
*/

#ifndef square_H
#define square_H

#include <iostream>

namespace mazelab
{
class square
{
  public:
    // STATUS CODES -- USE THESE CONSTANTS IN YOUR IMPLEMENTATION FILE
    //    (do not use the actual number values)

    // Kinds of squares:
    static const char WALL = '#';
    static const char START = 'S';
    static const char EXIT = 'E';
    static const char PLAIN = '-';

    // Visit status:
    static const char UNVISITED = '-';
    static const char WORKLIST = '@';
    static const char EXPLORED = '.';
    static const char SOLUTION = 'X';

    //
    //  Constructor with 3 parameters for square kind, row, and column
    //  Postcondition:  The new square status is UNVISITED with kind, row, 
    //     and col values initialized to sq_kind, row_val, and col_val, 
    //     respectively.
    //  Postcondition:  The `prev` pointer is initialized to NULL.
    //  Exception: Throws domain_error if sq_kind is invalid.
    //
    square(char sq_kind = WALL, int row_val = 0, int col_val = 0);

    // *** ACCESSORS *** //

    //
    // getKind
    //  Postcondition: Return value is the kind of square this is.
    char getKind() const { return kind; }

    //
    // getStatus
    //  Postcondition: Return value is the current status of the square.
    char getStatus() const { return status; }

    //
    // getRow
    //  Postcondition: Return value is the row where the square is located.
    //
    int getRow() const { return row; }

    //
    // getCol
    //  Postcondition: Return value is the column where the square is located.
    //
    int getCol() const { return col; }

    //
    // getPrev
    //  Postcondition: Return value is a pointer to a square.
    //
    square* getPrev() const { return prev; }

    //
    // isWallSquare
    //  Postcondition:  Return true square is WALL square; otherwise
    //     return false.
    //
    bool isWallSquare() const { return kind == WALL; }

    //
    // isStartSqare
    //  Postcondition:  Return true if square is a START square;
    //     otherwise, return false.
    //
    bool isStartSquare() const { return kind == START; }

    //
    // isExitSquare
    //  Postcondition:  Return true if square is an EXIT square;
    //     otherwise, return false.
    //
    bool isExitSquare() const { return kind == EXIT; }

    //
    // isPlainSquare
    //  Postcondition:  Return true if the square is a PLAIN square;
    //     otherwise, return false.
    //
    bool isPlainSquare() const { return kind == PLAIN; }

    //
    // isUnvisited
    //  Postcondition:  Return true if the square status is UNVISITED;
    //      otherwise, return false.
    //
    bool isUnvisited() const { return status == UNVISITED; }

    //
    // onWorklist:
    //  Postcondition:  Return true if the square status is WORKLIST;
    //      otherwise, return false.
    //
    bool onWorklist() const { return status == WORKLIST; }

    //
    // isExplored:
    //  Postcondition:  Return true if the square status is EXPLORED;
    //      otherwise, return false.
    //
    bool isExplored() const { return status == EXPLORED; }

    //
    // onSolutionPath:
    //  Postcondition:  Return true if the square status is SOLUTION;
    //      otherwise, return false.
    //
    bool onSolutionPath() const { return status == SOLUTION; }

    //
    // getPosition
    //  Postcondition: Return value is a string for reporting the coordinates
    //     of the square in the form "[row,col]".
    //
    //  Example: If the square is in row 5 and column 0, return "[5,0]".
    //
    std::string getPosition() const;

    // *** MODIFIERS *** //

    // setStatus
    //  Precondition:  This is not a WALL square.
    //  Precondition:  New status, s, is a valid square status.
    //  Postcondition: `status` is set to s.
    //  Exception: Throws domain_error if square is a WALL square.
    //  Exception: Throws domain_error if s is invalid.
    void setStatus(char new_status);

    //
    // setPrev
    //  Precondition:  This is not a WALL or START square.
    //  Postcondition:  This square's `prev` is set to ptr.
    //  Exception: Throws domain_error if square is WALL or START.
    //
    void setPrev(square* ptr);

  private:
    char kind;
    char status;
    int row;
    int col;
    square* prev;
};

//
// STREAM OUTPUT
//  Postcondition:  Puts a single char representing the square into the
//     output stream `out`, and returns `out` to allow for chaining.
//     If the square is a WALL, START, or EXIT square, output the square kind. 
//     If the square is am PLAIN square, output the square status.
//  Example: If sq.kind is WALL, the character `#` is put into the output
//     stream.
//  Example: If sq.kind is PLAIN and the square status is UNVISITED, 
//     the character `-` is put into the output stream.
//
std::ostream& operator<<(std::ostream& out, const square& sq);

}  // namespace mazelab

#endif /* square_H */
