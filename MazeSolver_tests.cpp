// FILE: maze_tests.cpp
// CS 223 Winter 2018, Lab 6
//
// Theresa Wilson and Barb Wahl
// Updated, April 2020
//

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "MazeSolver.h"
#include "gtest/gtest.h"  // declares the testing framework
#include "maze.h"

#define BACKWARD_HAS_DW 1
#include "backward.hpp"
backward::SignalHandling sh;

using namespace std;
using namespace mazelab;

namespace
{

const string maze_dir = "maze_files/";

TEST(TestMazeSolverOutputOperator, outputDFS)
{
    string maze("2 3 # - S E - - ");
    stringstream maze_stream1(maze);
    string expected = "Maze:\n"
        "# X S \n"
        "E X @ \n"
        "Worklist: [1,2]";

    MazeSolver solver(maze_stream1);
    string solverout = solver.solve(false);
    stringstream out;
    out << solver;
    EXPECT_EQ(out.str(), expected);

}

TEST(TestMazeSolverOutputOperator, outputBFS)
{
    string maze("2 3 # - S E - - ");
    stringstream maze_stream1(maze);
    string expected = "Maze:\n"
        "# . S \n"
        "E X X \n"
        "Worklist: ";

    MazeSolver solver(maze_stream1);
    string solverout = solver.solve(true);
    stringstream out;
    out << solver;
    EXPECT_EQ(out.str(), expected);

}

TEST(TestMazeSolverDFS, maze_b1)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_b1.txt";
    string solution = "[1,0] [0,0] [0,1] [0,2] [0,3] [1,3] [2,3] [2,2] [2,1]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(false);  // DFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverDFS, maze_t2)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_t2.txt";
    string solution = "[0,1] [1,1] [1,0] [2,0]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(false);  // DFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverDFS, maze_t3)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_t3.txt";
    string solution = "[0,1] [1,1]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(false);  // DFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverDFS, maze_unsolvable)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_unsolvable1.txt";
    string solution = "unsolvable!";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();
        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(false);  // DFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverDFS, maze_b2)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_b2.txt";
    string solution =
        "[3,7] [3,6] [2,6] [1,6] [1,5] [1,4] [1,3] [2,3] [3,3] [3,2] [3,1] "
        "[4,1] [5,1] [5,2] [5,3] [5,4] [5,5] [6,5] [7,5] [7,4] [7,3] [7,2]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(false);  // DFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverDFS, maze_b3)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_b3.txt";
    string solution = "[0,0] [1,0]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(false);  // DFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverDFS, maze_t4)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_t4.txt";
    string solution = "[1,0] [2,0] [2,1] [2,2] [1,2]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(false);  // DFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverDFS, maze_b4)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_b4.txt";
    string solution =
        "[3,7] [3,6] [2,6] [1,6] [1,5] [1,4] [1,3] [2,3] [3,3] [3,2] [3,1] "
        "[4,1] [5,1] [5,2] [5,3] [5,4] [5,5] [6,5] [7,5] [7,6] [7,7] [6,7]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(false);  // DFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverBFS, maze_b1)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_b1.txt";
    string solution = "[1,0] [0,0] [0,1] [0,2] [0,3] [1,3] [2,3] [2,2] [2,1]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(true);  // BFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverBFS, maze_t2)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_t2.txt";
    string solution = "[0,1] [1,1] [1,0] [2,0]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(true);  // BFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverBFS, maze_t3)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_t3.txt";
    string solution = "[0,1] [1,1]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(true);  // BFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverBFS, maze_unsolvable)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_unsolvable2.txt";
    string solution = "unsolvable!";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(true);  // BFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverBFS, maze_b2)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_b2.txt";
    string solution =
        "[3,7] [3,6] [2,6] [1,6] [1,5] [1,4] [1,3] [2,3] [3,3] [3,2] [3,1] "
        "[4,1] [5,1] [5,2] [5,3] [5,4] [5,5] [6,5] [7,5] [7,4] [7,3] [7,2]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(true);  // BFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverBFS, maze_b3)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_b3.txt";
    string solution = "[0,0] [1,0]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(true);  // BFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverBFS, maze_t4)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_t4.txt";
    string solution = "[1,0] [1,1] [1,2]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(true);  // BFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestMazeSolverBFS, maze_b4)
{
    bool show_details = false;
    string maze_to_solve = maze_dir + "maze_b4.txt";
    string solution = "[3,7] [4,7] [5,7] [6,7]";

    ifstream mazefile(maze_to_solve.c_str());
    if (!mazefile)
    {
        throw string("Unable to open file: " + maze_to_solve);
        ASSERT_FALSE(true);
    }

    try
    {
        MazeSolver solver(mazefile);
        mazefile.close();

        string solverout;
        if (show_details) cout << "\nMAZE: " + maze_to_solve << endl;
        solverout = solver.solve(true);  // BFS
        if (show_details) cout << "\nAfter solve: " << solver << endl;
        if (show_details) cout << "\n===>>> path found: " << solverout << endl << endl;
        ASSERT_EQ(solverout, solution);
    }
    catch (domain_error e)
    {
        cout << e.what();
        ASSERT_FALSE(true);
    }
}

TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_No_StartSquare)
{
    stringstream maze_stream;
    maze_stream << "3 1 0 0 2";
    try
    {
        MazeSolver solver(maze_stream);  // should throw domain_error
    }
    catch (domain_error)
    {
        EXPECT_TRUE(true);
        return;
    }
    EXPECT_TRUE(false);  // shouldn't make it here;
}
}  // end namespace

// main() for testing -- boilerplate
int main(int argc, char* argv[])
{
    testing::FLAGS_gtest_catch_exceptions = 0;
    testing::InitGoogleTest(&argc, argv);
    bool result = RUN_ALL_TESTS();

    cout << "\n\nNOTE: ";
    cout << "If a test fails, change the boolean variable `show_details` ";
    cout << "at the\ntop of the test to true, then compile and rerun. This ";
    cout << "will show additional\ninformation that should help with debugging.";
    cout << endl << endl;

    return result;
}
