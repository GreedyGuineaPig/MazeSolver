/*
*  MazeSolver.cpp -- Implementation of MazeSolver Class
*  Lab 6, CS 223
*
*  Name: Hiroki Nakano
*  Date: 11/4/2020
*
*  A MazeSolver has a worklist for managing the exploration of a maze, and a
*  specific maze to solve.  MazeSolver returns a path from Start to Exit if
*  such a path exists, or reports that the maze is unsolvable.
*
*  Instance variables:
*     maze * maze_ptr;  // pointer to the maze to be solved
*     std::deque <square *> worklist;
*/

#include "MazeSolver.h"

#include <cassert>    // provides assert
#include <sstream>    // provides string streams
#include <stdexcept>  // provides standard exceptions

using namespace std;
using namespace mazelab;

// implement your MazeSolver functions here...
MazeSolver::MazeSolver(std::istream& in)
{
    try{
        maze_ptr = new maze(in);
    }catch(domain_error& e){
        cout << e.what() << endl;
        throw domain_error("MazeSolver constructor error");
    }
    worklist.push_back(maze_ptr -> getStart());
}

MazeSolver::~MazeSolver()
{
    delete maze_ptr;
    maze_ptr = NULL;
    worklist.clear();
}

/*
*  get_path -- use the `prev` pointers of the maze squares to create a
*     deque of pointers to the squares in the path from the start to a
*     given square pointed to by `sq_ptr`.
*
*  Precondition: `sq_ptr` has been on or is currently on the worklist.
*
*  Postcondition: Return value is a deque of the squares in the path from
*     start to `sq_ptr`.  The front of the deque points to the start square
*     and the back contains `sq_ptr`.
*/
std::deque<mazelab::square*> MazeSolver::get_path(mazelab::square* sq_ptr)const
{
    deque<square*> squares;
    for (square* current_square = sq_ptr; current_square -> getPrev() != NULL;
     current_square = current_square -> getPrev())
    {
        squares.push_front(current_square);
    }
    squares.push_front(maze_ptr -> getStart());
    return squares;
}

/*
*  print_deque_of_squares -- Write the coordinates of the squares in
*     the deque in order from front to back, separated by spaces,
*     without a trailing space.
*
*  Postcondition: The return value contains the coordinates of the squares
*     in the deque in order from the front to the back.
*  Postcondition: The contents of deque have remained unchanged.
*
*  HINT: Use the deque iterators
*/
std::string MazeSolver::print_deque_of_squares(std::deque<mazelab::square*> squares)const
{
    // string path = maze_ptr -> getStart() -> getPosition() + " ";
    string path = "";
    square* current_square = NULL;
    for (auto iter = squares.begin(); iter != squares.end(); ++iter)
    {
        current_square = *iter;
        path += current_square -> getPosition() + " ";
    }
    path = path.substr(0, path.length() - 1);
    return path;
}

/*
*  mark_solution -- Mark the solution path from the start to the square
*  pointed to by `sq_ptr`.
*
*  Precondition: `squares` is a deque of square pointers for the squares
*     in a path starting at the pointer in the front and ending at the
*     pointer at the back.
*
*  Postcondition: Plain squares on the path have status = SOLUTION_PATH.
*/
void MazeSolver::mark_solution(std::deque<mazelab::square*> squares)
{
    square* current_square = NULL;
    for (auto iter = squares.begin(); iter != squares.end(); ++iter)
    {
        current_square = *iter;
        current_square -> setStatus(square::SOLUTION);
    }
}

/*
    *  step -- perform one iteration of the maze exploration algorithm
    *
    *  Postcondition: Return value is a pointer to the square that was just explored;
    *     if no square was explored on this step (e.g., step was called with
    *     an empty worklist), return value is NULL.
    *
    *  Postcondition: For any squares removed/added to the worklist, status has been
    *     appropriately updated.
    *
    *  NOTE: The withBFS parameter defaults to false.  If withBFS is `true`, treat
    *     the worklist as a queue, resulting in breadth-first maze search; otherwise,
    *     treat the worklist as a stack, resulting in depth-first search.
    */
mazelab::square* MazeSolver::step(bool withBFS)
{
    square* current_square = NULL;
    //true = breadth-first search
    if (withBFS)
    {
        current_square = worklist.front();
        worklist.pop_front();
    }
    else
    {
        current_square = worklist.back();
        worklist.pop_back();
    }
    return current_square;


}

std::string MazeSolver::solve(bool withBFS)
{
    square* current_square = NULL;
    square* tmp_square = NULL;
    vector<square*> v;
    deque<square*> squares;
    while (!worklist.empty())
    {
        current_square = step(withBFS);
        if (current_square -> isExitSquare())
        {
            squares = get_path(current_square);
            mark_solution(squares);
            return print_deque_of_squares(squares);
        }
        v = maze_ptr -> getNeighbors(current_square);
        for (auto iter = v.begin(); iter != v.end(); ++iter)
        {
            tmp_square = *iter;
            if (tmp_square -> getStatus() == square::UNVISITED)
            {
                tmp_square -> setStatus(square::WORKLIST);
                tmp_square -> setPrev(current_square);
                worklist.push_back(tmp_square);
            }
        }
        current_square -> setStatus(square::EXPLORED);
    }
    return "unsolvable!";
}

// FRIEND
/*
* output stream operator -- for printing the current state of the maze
*    and the worklist
*
* Print out a visual representation of the state of the maze as follows:
*
* Maze:
* <<<maze output as produced by maze operator<<  >>>
* Worklist: <<<output of print_deque_of_squares for worklist>>>
* NOTE: `out` is returned to allow for chained output
*/
std::ostream& operator<<(std::ostream& out, const MazeSolver& solver)
{
    out << "Maze:";
    out << *solver.maze_ptr;
    out << "Worklist: ";
    out << solver.print_deque_of_squares(solver.worklist);
    return out;
}

// Provided main function for very initial testing;
// REMOVE or COMMENT OUT this main function before you build
// and run with MazeSolver_test.cpp.

//  int main()
// {
    // string maze("2 3 0 3 1 2 3 3 ");
    // stringstream maze_stream1(maze);
    // MazeSolver solverDFS(maze_stream1);

    // cout << "Depth-first Search:\n";
    // string solverout = solverDFS.solve(false);
    // cout << solverDFS;
    // cout << "\nDFS path found: " << solverout << endl;

    // stringstream maze_stream2(maze);
    // MazeSolver solverBFS(maze_stream2);
    // cout << "\nBreadth-first Search:\n";
    // solverout = solverBFS.solve(true);
    // cout << solverBFS;
    // cout << "\nBFS path found: " << solverout << endl;

//     return 0;
// }
