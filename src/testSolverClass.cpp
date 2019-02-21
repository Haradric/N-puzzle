
#include "gtest/gtest.h"
#include "Solver.h"

static std::vector<int> blank3 = {
    1, 2, 3,
    8, 0, 4,
    7, 6, 5,
};

static std::vector<int> solvable3 = {
    3, 8, 0,
    2, 4, 1,
    5, 7, 6,
};

static std::vector<int> unsolvable3 = {
    8, 5, 2,
    1, 7, 3,
    0, 6, 4,
};

static std::vector<int> blank4 = {
     1,  2,  3,  4,
    12, 13, 14,  5,
    11,  0, 15,  6,
    10,  9,  8,  7,
};

static std::vector<int> solvable4 = {
     1,  2,  8,  9,
     0, 13,  6,  5,
    12, 15, 10,  3,
     7, 11, 14,  4,
};

static std::vector<int> unsolvable4 = {
     9,  5, 13, 12,
     4,  1,  0, 14,
     3, 10,  6,  8,
    11,  2,  7, 15,
};

static std::vector<int> blank5 = {
     1,  2,  3,  4,  5,
    16, 17, 18, 19,  6,
    15, 24,  0, 20,  7,
    14, 23, 22, 21,  8,
    13, 12, 11, 10,  9,
};

static std::vector<int> solvable5 = {
    23,  9, 15,  6,  0,
    17, 19,  1, 21,  2,
    10, 14,  7, 18, 16,
     3, 11, 13,  5,  4,
    12, 20,  8, 24, 22,
};

static std::vector<int> unsolvable5 = {
    15,  8, 11, 13, 16,
     3,  0,  2,  9,  6,
     7,  4, 22, 24, 23,
     5, 10, 12, 19, 17,
    14, 20,  1, 21, 18,
};

static std::vector<int> blank6 = {
     1,  2,  3,  4,  5,  6,
    20, 21, 22, 23, 24,  7,
    19, 32, 33, 34, 25,  8,
    18, 31,  0, 35, 26,  9,
    17, 30, 29, 28, 27, 10,
    16, 15, 14, 13, 12, 11,
};

static std::vector<int> solvable6 = {
    25, 20, 14, 17, 35, 21,
    13, 11, 29, 23,  0,  5,
    33,  3,  4,  9, 27, 34,
    22, 10, 26, 24, 18, 19,
    32,  7, 16,  2, 12, 30,
    28, 31,  8,  6,  1, 15,
};

static std::vector<int> unsolvable6 = {
    35, 13,  3,  1,  7,  4,
    29, 26, 34,  6,  9, 11,
    12, 14, 20, 32, 21, 23,
    31, 18,  0, 33, 19, 24,
    15, 16,  5, 22,  8, 25,
     2, 10, 27, 28, 30, 17,
};

static std::vector<int> blank7 = {
     1,  2,  3,  4,  5,  6,  7,
    24, 25, 26, 27, 28, 29,  8,
    23, 40, 41, 42, 43, 30,  9,
    22, 39, 48,  0, 44, 31, 10,
    21, 38, 47, 46, 45, 32, 11,
    20, 37, 36, 35, 34, 33, 12,
    19, 18, 17, 16, 15, 14, 13,
};

static std::vector<int> solvable7 = {
    26, 38, 16, 43, 40,  1,  2,
     7,  9, 47, 32,  6, 46, 10,
    28, 36, 37, 31, 12, 35, 41,
    22, 29, 39, 44,  5, 15,  8,
     0, 24, 23, 18, 34, 27,  3,
    17, 19, 13, 42, 45, 30, 11,
    33,  4, 14, 21, 20, 48, 25,
};

static std::vector<int> unsolvable7 = {
     2, 31,  4,  1,  9,  3, 47,
    43, 11, 27, 41, 29, 18, 20,
    44, 13,  6, 32,  8,  7, 10,
    36, 34, 19, 33, 46,  0, 28,
    26, 39, 23, 25, 15,  5, 14,
    16, 17, 30, 35, 24, 45, 48,
    21, 12, 38, 40, 42, 22, 37,
};

class SolverClass : public ::testing::Test {

protected:
    void SetUp() {
        b3.init(3, blank3);
        b4.init(4, blank4);
        b5.init(5, blank5);
        b6.init(6, blank6);
        b7.init(7, blank7);

        s3.init(3, solvable3);
        s4.init(4, solvable4);
        s5.init(5, solvable5);
        s6.init(6, solvable6);
        s7.init(7, solvable7);

        u3.init(3, unsolvable3);
        u4.init(4, unsolvable4);
        u5.init(5, unsolvable5);
        u6.init(6, unsolvable6);
        u7.init(7, unsolvable7);
    }
    void TearDown() {}

    Puzzle b3, b4, b5, b6, b7;
    Puzzle s3, s4, s5, s6, s7;
    Puzzle u3, u4, u5, u6, u7;
};

TEST_F(SolverClass, Positive_Parity) {

    EXPECT_EQ(Solver::CheckParity(b3, b3), true);
    EXPECT_EQ(Solver::CheckParity(b4, b4), true);
    EXPECT_EQ(Solver::CheckParity(b5, b5), true);
    EXPECT_EQ(Solver::CheckParity(b6, b6), true);
    EXPECT_EQ(Solver::CheckParity(b7, b7), true);

    EXPECT_EQ(Solver::CheckParity(s3, b3), true);
    EXPECT_EQ(Solver::CheckParity(s4, b4), true);
    EXPECT_EQ(Solver::CheckParity(s5, b5), true);
    EXPECT_EQ(Solver::CheckParity(s6, b6), true);
    EXPECT_EQ(Solver::CheckParity(s7, b7), true);

    EXPECT_EQ(Solver::CheckParity(u3, b3), false);
    EXPECT_EQ(Solver::CheckParity(u4, b4), false);
    EXPECT_EQ(Solver::CheckParity(u5, b5), false);
    EXPECT_EQ(Solver::CheckParity(u6, b6), false);
    EXPECT_EQ(Solver::CheckParity(u7, b7), false);
}

TEST_F(SolverClass, Negative_Parity) {

    EXPECT_EQ(Solver::CheckParity(b3, b4), false);
    EXPECT_EQ(Solver::CheckParity(b4, b5), false);
    EXPECT_EQ(Solver::CheckParity(b5, b6), false);
    EXPECT_EQ(Solver::CheckParity(b6, b7), false);
    EXPECT_EQ(Solver::CheckParity(b7, b3), false);
}

TEST_F(SolverClass, Positive_MisplacedTiles) {

    EXPECT_EQ(Solver::MisplacedTiles(b3, b3), 0);
    EXPECT_EQ(Solver::MisplacedTiles(b4, b4), 0);
    EXPECT_EQ(Solver::MisplacedTiles(b5, b5), 0);
    EXPECT_EQ(Solver::MisplacedTiles(b6, b6), 0);
    EXPECT_EQ(Solver::MisplacedTiles(b7, b7), 0);

    EXPECT_EQ(Solver::MisplacedTiles(s3, b3), 9);
    EXPECT_EQ(Solver::MisplacedTiles(s4, b4), 12);
    EXPECT_EQ(Solver::MisplacedTiles(s5, b5), 25);
//    EXPECT_EQ(Solver::MisplacedTiles(s6, b6), 0);
//    EXPECT_EQ(Solver::MisplacedTiles(s7, b7), 0);

    EXPECT_EQ(Solver::MisplacedTiles(u3, b3), 8);
    EXPECT_EQ(Solver::MisplacedTiles(u4, b4), 16);
    EXPECT_EQ(Solver::MisplacedTiles(u5, b5), 24);
//    EXPECT_EQ(Solver::MisplacedTiles(u6, b6), 0);
//    EXPECT_EQ(Solver::MisplacedTiles(u7, b7), 0);
}

TEST_F(SolverClass, Negative_MisplacedTiles) {

    EXPECT_EQ(Solver::MisplacedTiles(b3, b4), -1);
    EXPECT_EQ(Solver::MisplacedTiles(b4, b5), -1);
    EXPECT_EQ(Solver::MisplacedTiles(b5, b6), -1);
    EXPECT_EQ(Solver::MisplacedTiles(b6, b7), -1);
    EXPECT_EQ(Solver::MisplacedTiles(b7, b3), -1);
}

TEST_F(SolverClass, Positive_ManhattanDistance) {

    Puzzle test1(3, { 1, 2, 5, 3, 0, 6, 7, 4, 8 });
    Puzzle test2(3, { 1, 2, 3, 4, 5, 6, 7, 8, 0 });

    EXPECT_EQ(Solver::ManhattanDistance(test1, test2), 8);

    EXPECT_EQ(Solver::ManhattanDistance(b3, b3), 0);
    EXPECT_EQ(Solver::ManhattanDistance(b4, b4), 0);
    EXPECT_EQ(Solver::ManhattanDistance(b5, b5), 0);
    EXPECT_EQ(Solver::ManhattanDistance(b6, b6), 0);
    EXPECT_EQ(Solver::ManhattanDistance(b7, b7), 0);

    EXPECT_EQ(Solver::ManhattanDistance(s3, b3), 14);
    EXPECT_EQ(Solver::ManhattanDistance(s4, b4), 28);
    EXPECT_EQ(Solver::ManhattanDistance(s5, b5), 78);
//    EXPECT_EQ(Solver::ManhattanDistance(s6, b6), 0);
//    EXPECT_EQ(Solver::ManhattanDistance(s7, b7), 0);

    EXPECT_EQ(Solver::ManhattanDistance(u3, b3), 10);
    EXPECT_EQ(Solver::ManhattanDistance(u4, b4), 36);
    EXPECT_EQ(Solver::ManhattanDistance(u5, b5), 84);
//    EXPECT_EQ(Solver::ManhattanDistance(u6, b6), 0);
//    EXPECT_EQ(Solver::ManhattanDistance(b7, b7), 0);
}

TEST_F(SolverClass, Negative_ManhattanDistance) {

    EXPECT_EQ(Solver::ManhattanDistance(b3, b4), -1);
    EXPECT_EQ(Solver::ManhattanDistance(b4, b5), -1);
    EXPECT_EQ(Solver::ManhattanDistance(b5, b6), -1);
    EXPECT_EQ(Solver::ManhattanDistance(b6, b7), -1);
    EXPECT_EQ(Solver::ManhattanDistance(b7, b3), -1);
}

TEST_F(SolverClass, Positive_LinearConflict) {

    Puzzle test1(3, { 4, 2, 5, 1, 0, 6, 3, 8, 7 });
    Puzzle test2(3, { 1, 2, 3, 4, 5, 6, 7, 8, 0 });
    EXPECT_EQ(Solver::LinearConflict(test1, test2), 14);

    EXPECT_EQ(Solver::LinearConflict(b3, b3), 0);
    EXPECT_EQ(Solver::LinearConflict(b4, b4), 0);
    EXPECT_EQ(Solver::LinearConflict(b5, b5), 0);
    EXPECT_EQ(Solver::LinearConflict(b6, b6), 0);
    EXPECT_EQ(Solver::LinearConflict(b7, b7), 0);

    EXPECT_EQ(Solver::LinearConflict(s3, b3), 20);
    EXPECT_EQ(Solver::LinearConflict(s4, b4), 34);
    EXPECT_EQ(Solver::LinearConflict(s5, b5), 94);
//    EXPECT_EQ(Solver::LinearConflict(s6, b6), 0);
//    EXPECT_EQ(Solver::LinearConflict(s7, b7), 0);

    EXPECT_EQ(Solver::LinearConflict(u3, b3), 12);
    EXPECT_EQ(Solver::LinearConflict(u4, b4), 46);
    EXPECT_EQ(Solver::LinearConflict(u5, b5), 104);
//    EXPECT_EQ(Solver::LinearConflict(u6, b6), 0);
//    EXPECT_EQ(Solver::LinearConflict(b7, b7), 0);
}

TEST_F(SolverClass, Negative_LinearConflict) {

    EXPECT_EQ(Solver::LinearConflict(b3, b4), -1);
    EXPECT_EQ(Solver::LinearConflict(b4, b5), -1);
    EXPECT_EQ(Solver::LinearConflict(b5, b6), -1);
    EXPECT_EQ(Solver::LinearConflict(b6, b7), -1);
    EXPECT_EQ(Solver::LinearConflict(b7, b3), -1);
}
