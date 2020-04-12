/*
*  MazeSolver.h
*  MazeSolver header file for CS 223 - Lab 6
*
*  Barb Wahl, Theresa Wilson, and Haris Skiadas
*  Last updated, March 2020
*
*  DO NOT CHANGE THIS FILE
*
*  MazeSolver has two main data components:
*      1) a specific maze to solve
*      2) a worklist of squares that it uses to manage its maze exploration
*         while it searches for a solution to the maze.
*  A solution is a path of non-wall squares leading from the maze Start
*  to the maze Exit.
*
*  Instance Variables for the data components:
*     maze * maze_ptr, a pointer to the maze to be solved
*     std::deque <square *> worklist, a double-ended queue while searching the maze
*
*  If a maze solution exists, MazeSolver returns a solution path; otherwise,
*  MazeSolver reports that the maze is unsolvable.
*
*  ************************** MazeSolver Worklist **************************
*
*  The MazerSolver worklist contains pointers to squares in the maze that
*  the solver knows about but has not yet explored. Squares are always
*  removed from the front of the worklist. However, whether a square is
*  added to the front or the back of the worklist depends on whether the
*  worklist is acting as a stack or a queue.
*
*    - When acting as a stack, squares are added to the FRONT of the worklist.
*    - When acting as a queue, squares are added to the BACK of the worklist.
*
*  Treating the worklist as a stack results in a depth-first search (DFS) of the
*  maze. Treating the worklist as a queue gives a breadth-first search (BFS) of
*  the maze.
*
*  To get both stack and queue functionality out of the worklist, the worklist
*  is implemented as a deque (pronounced "deck" == double-ended-queue). Deques
*  allow elements to be efficiently added and removed from both the front and
*  the back of the data structure.
*
*   HELPFUL DEQUE METHODS: see http://www.cplusplus.com/reference/deque/deque/
*
*     - void push_front:      inserts a new element at the front
*     - void push_back:       inserts a new element at the back
*     - <element type> front: returns a reference to the front element
*     - void pop_front:       removes the front element
*     - <size_type> size:     returns the number of elements currently in the
*                                container
*     - bool empty:           returns true iff the container holds no elements
*     - void clear:           removes all elements, leaving the container with
*                                a size of 0
*
*  The Mazesolver "solve" and "step" functions both take the boolean parameter,
*  `withBFS`. If withBFS is set to true, MazeSolver performs breadth-first
*  search; otherwise, MazeSolver performs depth-first search. By default, the
*  `withBFS` paramater is set to false.  To solve the maze using breadth-first
*  search, call the solve function with the value true:
*
*      solve(true)
*
*  *********************** Maze Exploration Algorithm ***********************
*
*  At the start (i.e., In the constructor):
*     Create an empty worklist and add the Start square to the worklist.
*
*  Repeat the following to explore the maze until you find a solution or determine
*  the maze is unsolvable:
*
*  1. Try to take a step. Is the worklist empty? If so there are no more possible
*     steps to take, so you must:
*       - terminate the exploration of the maze
*
*  2. Otherwise, succeed in taking a step by grabbing the next square to explore
*     from the worklist (and removing it from the worklist).  Call this the
*     current square.
*
*  3. Does the current square correspond to the Exit square? If so:
*       - terminate the exploration of the maze
*
*  4. Otherwise, current square is a reachable non-Exit square that we haven't
*     explored yet. Explore it as follows:
*
*       - Check for neighboring squares in the following order:
*
*             North, East, South, West
*
*       - For each neighboring square "neighbor" that is not outside the maze
*         (of course) and is not a wall, if neighbor has NEVER BEEN ON THE WORKLIST:
*
*          a) update the `prev` field for neighbor to point to the current square
*          b) update the `status` field for neighbor unless it is the EXIT
*          c) add neighbor to the worklist
*
*  5. If the current square is a "plain" square (not the start or exit), update
*     the status of the current square to indicate it has been explored.
*
*  After the maze exploration has terminated:
*     - If no solution was found, return that the maze was unsolvable.
*     - Otherwise:
*          a) For each plain square on the discovered path from start to exit,
*             set the square's status to SOLUTION
*          b) Return the solution path.
*
*
*  IMPORTANT NOTES:
*
*  ! Square status: The status of a plain square *must be updated* whenever the
*    square is:
*
*      - added to the worklist
*      - removed from the worklist
*      - added to the solution path

*  ! A square is EXPLORED when it is _removed_ from the worklist and its neighbors
*    are checked and if need be added to the worklist. 
*/

#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include <deque>
#include <iostream>

#include "maze.h"

class MazeSolver
{
  public:
    /*
    *  Constructor with 1 parameter
    *
    *  Postcondition: the maze is created in dynamic memory using the given
    *     input stream and maze_ptr is initialized to point to the maze
    *
    *  Postcondition: the maze's start square has been added to the worklist
    *
    *  Exception: Throws domain_error if `in` does not contain a valid
    *     description of a maze.
    *
    *  NOTE: The input stream `in` holds a stream of tokens separated by
    *     whitespace and ending with whitespace, as described in maze.h.
    *
    *  HINT: Use a try-catch when initializing the maze to catch any
    *     exceptions thrown by the maze constructor.
    */
    explicit MazeSolver(std::istream& in);

    /*
    *  Destructor
    */
    ~MazeSolver();

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
    std::deque<mazelab::square*> get_path(mazelab::square* sq_ptr) const;

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
    std::string print_deque_of_squares(std::deque<mazelab::square*> squares) const;

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
    void mark_solution(std::deque<mazelab::square*> squares);

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
    mazelab::square* step(bool withBFS = false);

    /*
    *  solve
    *
    *  Postcondition: The return value is a string, holding either the solution
    *     path from Start to Exit, or "unsolvable!" if there is no solution path.
    *
    *  Postcondition: If a solution path was found, then every plain square on
    *     the path has its status set to square::SOLUTION_PATH.
    *
    *  NOTE: If withBFS is `true`, treat the worklist as a queue, resulting in
    *     breadth-first maze search; otherwise, treat the worklist as a stack,
    *     resulting in depth-first search.
    */
    std::string solve(bool withBFS = false);

    // friends
    friend std::ostream& operator<<(std::ostream& out, const MazeSolver& solver);

  private:
    // INSTANCE VARIABLES
    mazelab::maze* maze_ptr;
    std::deque<mazelab::square*> worklist;
};

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
std::ostream& operator<<(std::ostream& out, const MazeSolver& solver);

#endif /* MAZESOLVER_H */
