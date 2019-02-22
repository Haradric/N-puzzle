
#include "gtest/gtest.h"
#include "Puzzle.h"

static std::vector<std::size_t> blank3 = {
    1, 2, 3,
    8, 0, 4,
    7, 6, 5,
};

static std::vector<std::size_t> solvable3 = {
    3, 8, 0,
    2, 4, 1,
    5, 7, 6,
};

static std::vector<std::size_t> unsolvable3 = {
    8, 5, 2,
    1, 7, 3,
    0, 6, 4,
};

static std::vector<std::size_t> blank4 = {
     1,  2,  3,  4,
    12, 13, 14,  5,
    11,  0, 15,  6,
    10,  9,  8,  7,
};

static std::vector<std::size_t> solvable4 = {
     1,  2,  8,  9,
     0, 13,  6,  5,
    12, 15, 10,  3,
     7, 11, 14,  4,
};

static std::vector<std::size_t> unsolvable4 = {
     9,  5, 13, 12,
     4,  1,  0, 14,
     3, 10,  6,  8,
    11,  2,  7, 15,
};

static std::vector<std::size_t> blank5 = {
     1,  2,  3,  4,  5,
    16, 17, 18, 19,  6,
    15, 24,  0, 20,  7,
    14, 23, 22, 21,  8,
    13, 12, 11, 10,  9,
};

static std::vector<std::size_t> solvable5 = {
    23,  9, 15,  6,  0,
    17, 19,  1, 21,  2,
    10, 14,  7, 18, 16,
     3, 11, 13,  5,  4,
    12, 20,  8, 24, 22,
};

static std::vector<std::size_t> unsolvable5 = {
    15,  8, 11, 13, 16,
     3,  0,  2,  9,  6,
     7,  4, 22, 24, 23,
     5, 10, 12, 19, 17,
    14, 20,  1, 21, 18,
};

static std::vector<std::size_t> blank6 = {
     1,  2,  3,  4,  5,  6,
    20, 21, 22, 23, 24,  7,
    19, 32, 33, 34, 25,  8,
    18, 31,  0, 35, 26,  9,
    17, 30, 29, 28, 27, 10,
    16, 15, 14, 13, 12, 11,
};

static std::vector<std::size_t> solvable6 = {
    25, 20, 14, 17, 35, 21,
    13, 11, 29, 23,  0,  5,
    33,  3,  4,  9, 27, 34,
    22, 10, 26, 24, 18, 19,
    32,  7, 16,  2, 12, 30,
    28, 31,  8,  6,  1, 15,
};

static std::vector<std::size_t> unsolvable6 = {
    35, 13,  3,  1,  7,  4,
    29, 26, 34,  6,  9, 11,
    12, 14, 20, 32, 21, 23,
    31, 18,  0, 33, 19, 24,
    15, 16,  5, 22,  8, 25,
     2, 10, 27, 28, 30, 17,
};

static std::vector<std::size_t> blank7 = {
     1,  2,  3,  4,  5,  6,  7,
    24, 25, 26, 27, 28, 29,  8,
    23, 40, 41, 42, 43, 30,  9,
    22, 39, 48,  0, 44, 31, 10,
    21, 38, 47, 46, 45, 32, 11,
    20, 37, 36, 35, 34, 33, 12,
    19, 18, 17, 16, 15, 14, 13,
};

static std::vector<std::size_t> solvable7 = {
    26, 38, 16, 43, 40,  1,  2,
     7,  9, 47, 32,  6, 46, 10,
    28, 36, 37, 31, 12, 35, 41,
    22, 29, 39, 44,  5, 15,  8,
     0, 24, 23, 18, 34, 27,  3,
    17, 19, 13, 42, 45, 30, 11,
    33,  4, 14, 21, 20, 48, 25,
};

static std::vector<std::size_t> unsolvable7 = {
     2, 31,  4,  1,  9,  3, 47,
    43, 11, 27, 41, 29, 18, 20,
    44, 13,  6, 32,  8,  7, 10,
    36, 34, 19, 33, 46,  0, 28,
    26, 39, 23, 25, 15,  5, 14,
    16, 17, 30, 35, 24, 45, 48,
    21, 12, 38, 40, 42, 22, 37,
};

static Puzzle b3(3, blank3);
static Puzzle b4(4, blank4);
static Puzzle b5(5, blank5);
static Puzzle b6(6, blank6);
static Puzzle b7(7, blank7);

static Puzzle s3(3, solvable3);
static Puzzle s4(4, solvable4);
static Puzzle s5(5, solvable5);
static Puzzle s6(6, solvable6);
static Puzzle s7(7, solvable7);

static Puzzle u3(3, unsolvable3);
static Puzzle u4(4, unsolvable4);
static Puzzle u5(5, unsolvable5);
static Puzzle u6(6, unsolvable6);
static Puzzle u7(7, unsolvable7);

TEST(PuzzleClass, Positive_Constructor) {

    EXPECT_NO_THROW(Puzzle p(3, blank3));
    EXPECT_NO_THROW(Puzzle p(4, blank4));
    EXPECT_NO_THROW(Puzzle p(5, blank5));
    EXPECT_NO_THROW(Puzzle p(6, blank6));
    EXPECT_NO_THROW(Puzzle p(7, blank7));

    EXPECT_EQ(s3.tiles, solvable3);
    EXPECT_EQ(s4.tiles, solvable4);
    EXPECT_EQ(s5.tiles, solvable5);
    EXPECT_EQ(s6.tiles, solvable6);
    EXPECT_EQ(s7.tiles, solvable7);

    Puzzle z3(s3);
    Puzzle z4(s4);
    Puzzle z5(s5);
    Puzzle z6(s6);
    Puzzle z7(s7);

    EXPECT_EQ(z3, s3);
    EXPECT_EQ(z4, s4);
    EXPECT_EQ(z5, s5);
    EXPECT_EQ(z6, s6);
    EXPECT_EQ(z7, s7);

//    EXPECT_NO_THROW(Puzzle move(b3, Puzzle::UP));
//    EXPECT_NO_THROW(Puzzle move(b3, Puzzle::DOWN));
//    EXPECT_NO_THROW(Puzzle move(b3, Puzzle::LEFT));
//    EXPECT_NO_THROW(Puzzle move(b3, Puzzle::RIGHT));
//
//    EXPECT_NO_THROW(Puzzle move(s3, Puzzle::UP));
//    EXPECT_NO_THROW(Puzzle move(s3, Puzzle::RIGHT));
//
//    EXPECT_NO_THROW(Puzzle move(u3, Puzzle::DOWN));
//    EXPECT_NO_THROW(Puzzle move(u3, Puzzle::LEFT));
//
//    Puzzle move1(s3, Puzzle::UP);
//    Puzzle move2(s3, Puzzle::RIGHT);
//    Puzzle move3(u3, Puzzle::DOWN);
//    Puzzle move4(u3, Puzzle::LEFT);
//    EXPECT_EQ(move1.tiles, std::vector<std::size_t>({ 3, 8, 1, 2, 4, 0, 5, 7, 6 }));
//    EXPECT_EQ(move2.tiles, std::vector<std::size_t>({ 3, 0, 8, 2, 4, 1, 5, 7, 6 }));
//    EXPECT_EQ(move3.tiles, std::vector<std::size_t>({ 8, 5, 2, 0, 7, 3, 1, 6, 4 }));
//    EXPECT_EQ(move4.tiles, std::vector<std::size_t>({ 8, 5, 2, 1, 7, 3, 6, 0, 4 }));
}

TEST(PuzzleClass, Negative_Constructor) {

    EXPECT_THROW(Puzzle p1(0, std::vector<std::size_t>(0)), std::exception);
    EXPECT_THROW(Puzzle p1(1, { 1 }),               std::exception);
    EXPECT_THROW(Puzzle p1(2, { 0, 1, 2, 3 }),      std::exception);

    EXPECT_THROW(Puzzle p1(3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 }),    std::exception);
    EXPECT_THROW(Puzzle p1(3, { 1, 1, 1, 1, 1, 1, 1, 1, 1 }),    std::exception);
    EXPECT_THROW(Puzzle p1(3, { 0, 1, 2, 3, 4, 5, 6, 7 }),       std::exception);
    EXPECT_THROW(Puzzle p1(3, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), std::exception);

//    EXPECT_THROW(Puzzle move(s3, Puzzle::DOWN),  std::exception);
//    EXPECT_THROW(Puzzle move(s3, Puzzle::LEFT),  std::exception);
//    EXPECT_THROW(Puzzle move(u3, Puzzle::UP),    std::exception);
//    EXPECT_THROW(Puzzle move(u3, Puzzle::RIGHT), std::exception);
//
//    EXPECT_THROW(Puzzle move(s3, 5), std::exception);
}

//TEST_F(PuzzleClass, Positive_updateScore) {
//
//    s3.updateScore(MisplacedTiles, b3);
//    s4.updateScore(MisplacedTiles, b4);
//    s5.updateScore(MisplacedTiles, b5);
//    s6.updateScore(MisplacedTiles, b6);
//    s7.updateScore(MisplacedTiles, b7);
//
////    EXPECT_EQ(<#val1#>, <#val2#>);
//}

//TEST_F(PuzzleClass, Negative_updateScore) {
//
//    b3.updateScore(MisplacedTiles, b4);
//}
