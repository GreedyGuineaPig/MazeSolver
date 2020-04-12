// square.cpp -- Implementation of Square Class
// CS 223, Lab 6
//
// Name: Theresa Wilson
// Date: 3-26-2020
//

#include "square.h"

#include <sstream>
#include <stdexcept>

using namespace std;

namespace mazelab
{

// Kinds of squares:
const char WALL = square::WALL;
const char START = square::START;
const char EXIT = square::EXIT;
const char PLAIN = square::PLAIN;

// Visit status:
const char UNVISITED = square::UNVISITED;
const char WORKLIST = square::WORKLIST;
const char EXPLORED = square::EXPLORED;
const char SOLUTION = square::SOLUTION;

// Helper functions
bool isValidKind(const char sq_kind);
bool isValidStatus(const char s);

//
//  Constructor with 3 parameters for square kind, row, and column
//  Postcondition:  The new square status is UNVISITED with kind, row,
//     and col values initialized to sq_kind, row_val, and col_val,
//     respectively.
//  Postcondition:  The `prev` pointer is initialized to NULL.
//  Exception: Throws domain_error if sq_kind is invalid.
//
square::square(char sq_kind, int row_val, int col_val)
{
    if (isValidKind(sq_kind))
    {
    	kind = sq_kind;
    }
    else throw domain_error("Square kind is invalid.");

    status = UNVISITED;
    row = row_val;
    col = col_val;
    prev = NULL;
}

// *** ACCESSORS *** //

//
// getPosition
//  Postcondition: Return value is a string for reporting the coordinates
//     of the square in the form "[row,col]".
//
//  Example: If the square is in row 5 and column 0, return "[5,0]".
//
string square::getPosition() const
{
    stringstream temp;
    temp << "[" << row << "," << col << "]";
    return temp.str();
}

// *** MODIFIERS *** //

//
// setStatus
//  Precondition:  This is not a WALL square.
//  Precondition:  New status, s, is a valid square status.
//  Postcondition: `status` is set to s.
//  Exception: Throws domain_error if square is a WALL square.
//  Exception: Throws domain_error if s is invalid.
//
void square::setStatus(char s)
{
    if (isWallSquare())
        throw domain_error("Cannot change status of WALL squares.");
    else if (isValidStatus(s))
		status = s;
    else
        throw domain_error("Given status is invalid.");
}

//
// setPrev
//  Precondition:  This is not a WALL or START square.
//  Postcondition:  This square's `prev` is set to ptr.
//  Exception: Throws domain_error if square is WALL or START.
//
void square::setPrev(square* ptr)
{
    if (isWallSquare() || isStartSquare())
        throw domain_error("Cannot change prev on WALL or START squares.");
    else
        prev = ptr;
}

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
ostream& operator<<(ostream& out, const square& sq)
{
    if (sq.isPlainSquare())
        out << sq.getStatus();
    else
        out << sq.getKind();
    return out;
}

// Helper functions
bool isValidKind(const char sq_kind)
{
    return sq_kind == WALL || sq_kind == START ||
           sq_kind == EXIT || sq_kind == PLAIN;
}

bool isValidStatus(const char s)
{
    return s == UNVISITED || s == WORKLIST || s == EXPLORED || s == SOLUTION;
}

}  // namespace mazelab
