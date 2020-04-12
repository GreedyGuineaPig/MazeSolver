// FILE: maze_tests.cpp
// CS 223 Winter 2018, Lab 6
// Provided tests by T. Wilson and B. Wahl, updated March 2020
//
// Hiroki Nakano
// 11/4/2020

#include "gtest/gtest.h"  // declares the testing framework
#include "maze.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#define BACKWARD_HAS_DW 1
#include "backward.hpp"
backward::SignalHandling sh;

using namespace std;
using namespace mazelab;

namespace
{
// Lab 6 Unit Testing Plan (maze class) -- 34 tests, 25 of which are provided

// 7 tests for BasicMazeFunctionalityWithStringstream
//   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetNumRows_and_GetNumCols
//   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetStart
//   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetExit
//   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_0
//   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_1
//   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_2
//   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_3

// 5 tests for BasicMazeFunctionalityWithMazeFile
//   - 3_by_2_maze_t2_Test_GetNumRows_and_GetNumCols
//   - 3_by_2_maze_t2_Test_GetStart
//   - 3_by_2_maze_t2_Test_GetExit
//   - 3_by_2_maze_t2_Test_Get_at_0_0
//   - 3_by_2_maze_t2_Test_Get_at_1_0

// 9 tests for getNeighbors
//   - GetNeighbors_of_Interior_Square  <<< NOT PROVIDED
//   - GetNeighbors_of_Square_in_UpperLeftCorner  <<< NOT PROVIDED
//   - GetNeighbors_of_Square_in_UpperRightCorner  <<< NOT PROVIDED
//   - GetNeighbors_of_Square_in_LowerLeftCorner  <<< NOT PROVIDED
//   - GetNeighbors_of_Square_in_LowerRightCorner  <<< NOT PROVIDED
//   - GetNeighbors_of_Square_on_UpperMiddleEdge  <<< NOT PROVIDED
//   - GetNeighbors_of_Square_on_RightMiddleEdge  <<< NOT PROVIDED
//   - GetNeighbors_of_Square_on_LowerMiddleEdge  <<< NOT PROVIDED
//   - GetNeighbors_of_Square_on_LeftMiddleEdge  <<< NOT PROVIDED

// 2 tests for stream output
//   - Send_maze_with_All_Square_Kinds_and_Statuses_to_OutputStream
//   - OutputStream_Chaining

// 11 tests for exception handling
//   - DomainError_Thrown_when_Maze_Has_Invalid_Number_of_Rows
//   - DomainError_Thrown_when_Maze_Has_Invalid_Number_of_Columns
//   - DomainError_Thrown_when_Maze_Has_Square_With_Invalid_Kind_Z
//   - DomainError_Thrown_when_Maze_Has_No_StartSquare
//   - DomainError_Thrown_when_Maze_Has_Multiple_StartSquares
//   - DomainError_Thrown_when_Maze_Has_No_ExitSquare
//   - DomainError_Thrown_when_Maze_Has_Multiple_ExitSquares
//   - Out_of_Range_Thrown_when_Getting_SquarePointer_at_Row_NegativeOne
//   - Out_of_Range_Thrown_when_Getting_SquarePointer_at_Row_NumRows
//   - Out_of_Range_Thrown_when_Getting_SquarePointer_at_Col_NegativeOne
//   - Out_of_Range_Thrown_when_Getting_SquarePointer_at_Col_NumCols

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

// Maze directory:
const string maze_dir = "maze_files/";

// Test Constructor and Basic Getters
//  The basic maze class functionality (constructor, destructor,
//  getStart, getExit, getNumRows, getNumCols, get) is tested
//  first using a 1 x 4 maze inserted into a stringstream.

TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetNumRows_and_GetNumCols)
{
    stringstream maze_stream;
    maze_stream << "1 4 # E - S ";
    maze m1(maze_stream);

    EXPECT_EQ(m1.getNumRows(), 1);
    EXPECT_EQ(m1.getNumCols(), 4);
}

TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetStart)
{
    stringstream maze_stream;
    maze_stream << "1 4 # E - S ";
    maze m1(maze_stream);

    square* start_ptr = NULL;
    start_ptr = m1.getStart();
    ASSERT_TRUE(start_ptr != NULL);
    EXPECT_TRUE(start_ptr->isStartSquare());
    EXPECT_EQ(start_ptr->getPosition(), "[0,3]");
}

TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetExit)
{
    stringstream maze_stream;
    maze_stream << "1 4 # E - S ";
    maze m1(maze_stream);

    square* exit_ptr = NULL;
    exit_ptr = m1.getExit();
    ASSERT_TRUE(exit_ptr != NULL);
    EXPECT_TRUE(exit_ptr->isExitSquare());
    EXPECT_EQ(exit_ptr->getPosition(), "[0,1]");
}

TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_0)
{
    stringstream maze_stream;
    maze_stream << "1 4 # E - S ";
    maze m1(maze_stream);

    square* sq_ptr = NULL;
    sq_ptr = m1.get(0, 0);
    ASSERT_TRUE(sq_ptr != NULL);
    EXPECT_TRUE(sq_ptr->isWallSquare());
    EXPECT_EQ(sq_ptr->getPosition(), "[0,0]");
}

TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_1)
{
    stringstream maze_stream;
    maze_stream << "1 4 # E - S ";
    maze m1(maze_stream);

    square* sq_ptr = NULL;
    sq_ptr = m1.get(0, 1);
    ASSERT_TRUE(sq_ptr != NULL);
    EXPECT_TRUE(sq_ptr->isExitSquare());
    EXPECT_EQ(sq_ptr->getPosition(), "[0,1]");
}

TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_2)
{
    stringstream maze_stream;
    maze_stream << "1 4 # E - S ";
    maze m1(maze_stream);

    square* sq_ptr = NULL;
    sq_ptr = m1.get(0, 2);
    ASSERT_TRUE(sq_ptr != NULL);
    EXPECT_EQ(sq_ptr->getStatus(), UNVISITED);
    EXPECT_EQ(sq_ptr->getPosition(), "[0,2]");
}

TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_3)
{
    stringstream maze_stream;
    maze_stream << "1 4 # E - S ";
    maze m1(maze_stream);

    square* sq_ptr = NULL;
    sq_ptr = m1.get(0, 3);
    ASSERT_TRUE(sq_ptr != NULL);
    EXPECT_TRUE(sq_ptr->isStartSquare());
    EXPECT_EQ(sq_ptr->getPosition(), "[0,3]");
}

// Test Constructor and Basic Getters
//  The basic maze class functionality (constructor, destructor,
//  getStart, getExit, getNumRows, getNumCols, get) is tested
//  next using the 3 x 2 maze in the file: maze_t2.txt

TEST(TestBasicMazeFunctionalityWithMazeFile, 3_by_2_maze_t2_Test_GetNumRows_and_GetNumCols)
{
    // contents of maze_t2.txt:
    // 3 2
    // # S
    // - -
    // E #

    ifstream mazefile(maze_dir + "maze_t2.txt");
    maze m1(mazefile);

    EXPECT_EQ(m1.getNumRows(), 3);
    EXPECT_EQ(m1.getNumCols(), 2);
}

TEST(TestBasicMazeFunctionalityWithMazeFile, 3_by_2_maze_t2_Test_GetStart)
{
    // contents of maze_t2.txt:
    // 3 2
    // 0 1 3 3 2 0
    ifstream mazefile(maze_dir + "maze_t2.txt");
    maze m1(mazefile);

    square* start_ptr = NULL;
    start_ptr = m1.getStart();
    ASSERT_TRUE(start_ptr != NULL);
    EXPECT_TRUE(start_ptr->isStartSquare());
    EXPECT_EQ(start_ptr->getPosition(), "[0,1]");
}

TEST(TestBasicMazeFunctionalityWithMazeFile, 3_by_2_maze_t2_Test_GetExit)
{
    // contents of maze_t2.txt:
    // 3 2
    // 0 1 3 3 2 0
    ifstream mazefile(maze_dir + "maze_t2.txt");
    maze m1(mazefile);

    square* exit_ptr = NULL;
    exit_ptr = m1.getExit();
    ASSERT_TRUE(exit_ptr != NULL);
    EXPECT_TRUE(exit_ptr->isExitSquare());
    EXPECT_EQ(exit_ptr->getPosition(), "[2,0]");
}

TEST(TestBasicMazeFunctionalityWithMazeFile, 3_by_2_maze_t2_Test_Get_at_0_0)
{
    // contents of maze_t2.txt:
    // 3 2
    // 0 1 3 3 2 0
    ifstream mazefile(maze_dir + "maze_t2.txt");
    maze m1(mazefile);

    square* sq_ptr = NULL;
    sq_ptr = m1.get(0, 0);
    ASSERT_TRUE(sq_ptr != NULL);
    EXPECT_TRUE(sq_ptr->isWallSquare());
    EXPECT_EQ(sq_ptr->getPosition(), "[0,0]");
}

TEST(TestBasicMazeFunctionalityWithMazeFile, 3_by_2_maze_t2_Test_Get_at_1_0)
{
    // contents of maze_t2.txt:
    // 3 2
    // 0 1 3 3 2 0
    ifstream mazefile(maze_dir + "maze_t2.txt");
    maze m1(mazefile);

    square* sq_ptr = NULL;
    sq_ptr = m1.get(1, 0);
    ASSERT_TRUE(sq_ptr != NULL);
    EXPECT_EQ(sq_ptr->getStatus(), UNVISITED);
    EXPECT_EQ(sq_ptr->getPosition(), "[1,0]");
}


// Test getNeighbors
//
// STOP!
//
// Take some times to plan your getNeighbors tests:
//   - What should the maze look like that you want to test?
//   - How will you check that the the vector returned by getNeighbors
//     has the correct squares in the correct order?
//
// Reminder yourself about vector member functions and supported operatorsr:
//   - What constructors are supported?
//   - Are comparison operators supported?

TEST(TestGetNeighbors, GetNeighbors_of_Interior_Square)
{
    stringstream maze_stream;
    maze_stream << "3 3 # # # S - # # - E";
    maze m1(maze_stream);
    // ###
    // S-#
    // #-E

    square* sq_ptr = NULL;
    sq_ptr = m1.get(1, 1);
    vector<square*> v;
    v = m1.getNeighbors(sq_ptr);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(m1.get(2, 1), v.at(0));
    EXPECT_EQ(m1.get(1, 0), v.at(1));
}

TEST(TestGetNeighbors, GetNeighbors_of_Square_in_UpperLeftCorner)
{
    stringstream maze_stream;
    maze_stream << "3 3 # # # S - # # - E";
    maze m1(maze_stream);
    // ###
    // S-#
    // #-E

    square* sq_ptr = NULL;
    sq_ptr = m1.get(0, 0);
    vector<square*> v;
    v = m1.getNeighbors(sq_ptr);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(m1.get(1, 0), v.at(0));
}

TEST(TestGetNeighbors, GetNeighbors_of_Square_in_UpperRightCorner)
{
    stringstream maze_stream;
    maze_stream << "3 3 # # # S - # # - E";
    maze m1(maze_stream);
    // ###
    // S-#
    // #-E

    square* sq_ptr = NULL;
    sq_ptr = m1.get(0, 2);
    vector<square*> v;
    v = m1.getNeighbors(sq_ptr);
    EXPECT_EQ(v.size(), 0);
}

TEST(TestGetNeighbors, GetNeighbors_of_Square_in_LowerLeftCorner)
{
    stringstream maze_stream;
    maze_stream << "3 3 # # # S - # # - E";
    maze m1(maze_stream);
    // ###
    // S-#
    // #-E

    square* sq_ptr = NULL;
    sq_ptr = m1.get(2, 0);
    vector<square*> v;
    v = m1.getNeighbors(sq_ptr);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(m1.get(1, 0), v.at(0));
    EXPECT_EQ(m1.get(2, 1), v.at(1));
}

TEST(TestGetNeighbors, GetNeighbors_of_Square_in_LowerRightCorner)
{
    stringstream maze_stream;
    maze_stream << "3 3 # # # S - # # - E";
    maze m1(maze_stream);
    // ###
    // S-#
    // #-E

    square* sq_ptr = NULL;
    sq_ptr = m1.get(2, 2);
    vector<square*> v;
    v = m1.getNeighbors(sq_ptr);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(m1.get(2, 1), v.at(0));
}

TEST(TestGetNeighbors, GetNeighbors_of_Square_on_UpperMiddleEdge)
{
    stringstream maze_stream;
    maze_stream << "3 3 # # # S - # # - E";
    maze m1(maze_stream);
    // ###
    // S-#
    // #-E

    square* sq_ptr = NULL;
    sq_ptr = m1.get(0, 1);
    vector<square*> v;
    v = m1.getNeighbors(sq_ptr);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(m1.get(1, 1), v.at(0));
}

TEST(TestGetNeighbors, GetNeighbors_of_Square_on_RightMiddleEdge)
{
    stringstream maze_stream;
    maze_stream << "3 3 # # # S - # # - E";
    maze m1(maze_stream);
    // ###
    // S-#
    // #-E

    square* sq_ptr = NULL;
    sq_ptr = m1.get(1, 2);
    vector<square*> v;
    v = m1.getNeighbors(sq_ptr);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(m1.get(2, 2), v.at(0));
    EXPECT_EQ(m1.get(1, 1), v.at(1));
}

TEST(TestGetNeighbors, GetNeighbors_of_Square_on_LowerMiddleEdge)
{
    stringstream maze_stream;
    maze_stream << "3 3 # # # S - # # - E";
    maze m1(maze_stream);
    // ###
    // S-#
    // #-E

    square* sq_ptr = NULL;
    sq_ptr = m1.get(2, 1);
    vector<square*> v;
    v = m1.getNeighbors(sq_ptr);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(m1.get(1, 1), v.at(0));
    EXPECT_EQ(m1.get(2, 2), v.at(1));
}

TEST(TestGetNeighbors, GetNeighbors_of_Square_on_LeftMiddleEdge)
{
    stringstream maze_stream;
    maze_stream << "3 3 # # # S - # # - E";
    maze m1(maze_stream);
    // ###
    // S-#
    // #-E

    square* sq_ptr = NULL;
    sq_ptr = m1.get(2, 0);
    vector<square*> v;
    v = m1.getNeighbors(sq_ptr);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(m1.get(1, 0), v.at(0));
    EXPECT_EQ(m1.get(2, 1), v.at(1));
}

// Test stream output

TEST(TestStreamOutput, Send_maze_with_All_Square_Kinds_and_Statuses_to_OutputStream)
{
    stringstream maze_stream, out;
    maze_stream << "3 4 - - - - S # # - # E - - ";
    maze m1(maze_stream);
    m1.get(0,0)->setStatus('.');
    m1.get(0,1)->setStatus('.');
    m1.get(0,2)->setStatus('@');

    string correct = "\n. . @ - \nS # # - \n# E - - \n";

    out << m1;
    string actual = out.str();
    EXPECT_EQ(actual, correct);
}

TEST(TestStreamOutput, OutputStream_Chaining)
{
    stringstream out;
    ifstream mazefile1(maze_dir + "maze_b3.txt");
    maze m1(mazefile1);
    ifstream mazefile2(maze_dir + "maze_b1.txt");
    maze m2(mazefile2);

    string correct1 = "\nS \nE \n";
    string correct2 = "\n- - - - \nS # # - \n# E - - \n";
    string correct = correct1 + correct2;

    out << m1 << m2;
    string actual = out.str();
    EXPECT_EQ(actual, correct);
}

// Test exceptions

TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_Invalid_Number_of_Rows)
{
    stringstream maze_stream;
    maze_stream << "0 1 # S E";
    EXPECT_THROW(maze m1(maze_stream), domain_error);
}

TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_Invalid_Number_of_Columns)
{
    stringstream maze_stream;
    maze_stream << "1 0 # S E";
    EXPECT_THROW(maze m1(maze_stream), domain_error);
}

TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_Square_With_Invalid_Kind_Z)
{
    stringstream maze_stream;
    maze_stream << "3 1 # # Z";
    EXPECT_THROW(maze m1(maze_stream), domain_error);
}

TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_No_StartSquare)
{
    stringstream maze_stream;
    maze_stream << "3 1 # # E";
    EXPECT_THROW(maze m1(maze_stream), domain_error);
}

TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_Multiple_StartSquares)
{
    stringstream maze_stream;
    maze_stream << "3 1 E S S";
    EXPECT_THROW(maze m1(maze_stream), domain_error);
}

TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_No_ExitSquare)
{
    stringstream maze_stream;
    maze_stream << "3 1 # # E";
    EXPECT_THROW(maze m1(maze_stream), domain_error);
}

TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_Multiple_ExitSquares)
{
    stringstream maze_stream;
    maze_stream << "3 1 E E S";
    EXPECT_THROW(maze m1(maze_stream), domain_error);
}

TEST(TestExceptions, Out_of_Range_Thrown_when_Getting_SquarePointer_at_Row_NegativeOne)
{
    stringstream maze_stream;
    maze_stream << "3 1 # S E";
    maze m1(maze_stream);
    EXPECT_THROW(m1.get(-1, 0), out_of_range);
}

TEST(TestExceptions, Out_of_Range_Thrown_when_Getting_SquarePointer_at_Row_NumRows)
{
    stringstream maze_stream;
    maze_stream << "3 1 # S E";
    maze m1(maze_stream);
    EXPECT_THROW(m1.get(m1.getNumRows(), 0), out_of_range);
}

TEST(TestExceptions, Out_of_Range_Thrown_when_Getting_SquarePointer_at_Col_NegativeOne)
{
    stringstream maze_stream;
    maze_stream << "3 1 # S E";
    maze m1(maze_stream);
    EXPECT_THROW(m1.get(0, -1), out_of_range);
}

TEST(TestExceptions, Out_of_Range_Thrown_when_Getting_SquarePointer_at_Col_NumCols)
{
    stringstream maze_stream;
    maze_stream << "3 1 # S E";
    maze m1(maze_stream);
    EXPECT_THROW(m1.get(0, m1.getNumCols()), out_of_range);
}

}  // end namespace

// main() for testing -- boilerplate
int main(int argc, char* argv[])
{
    testing::FLAGS_gtest_catch_exceptions = 0;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
