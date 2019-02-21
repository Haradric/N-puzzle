
#include "InputParser.h"
#include "Solver.h"
#include "Puzzle.h"

#include <vector>
#include <iostream>

std::vector<int> solvable3 = {
    3, 8, 0,
    2, 4, 1,
    5, 7, 6,
};

std::vector<int> solvable4 = {
    1,  2,  8,  9,
    0, 13,  6,  5,
    12, 15, 10,  3,
    7, 11, 14,  4,
};

std::vector<int> solvable5 = {
    23,  9, 15,  6,  0,
    17, 19,  1, 21,  2,
    10, 14,  7, 18, 16,
    3, 11, 13,  5,  4,
    12, 20,  8, 24, 22,
};

std::vector<int> solvable6 = {
    25, 20, 14, 17, 35, 21,
    13, 11, 29, 23,  0,  5,
    33,  3,  4,  9, 27, 34,
    22, 10, 26, 24, 18, 19,
    32,  7, 16,  2, 12, 30,
    28, 31,  8,  6,  1, 15,
};

std::vector<int> solvable7 = {
    26, 38, 16, 43, 40,  1,  2,
    7,  9, 47, 32,  6, 46, 10,
    28, 36, 37, 31, 12, 35, 41,
    22, 29, 39, 44,  5, 15,  8,
    0, 24, 23, 18, 34, 27,  3,
    17, 19, 13, 42, 45, 30, 11,
    33,  4, 14, 21, 20, 48, 25,
};


std::string read_input(void);

int main(int ac, const char **av) {

    std::string opt_str[] = {"input", "output"};
    InputParser config;

    config.register_option(InputParser::STRING, opt_str, sizeof(opt_str)/sizeof(*opt_str));
    config.read_args(ac, av);

//    std::cout << config << std::endl;

    try {
        Solver solver(3, solvable3, Solver::LinearConflict);
//        Solver solver(4, solvable4, LinearConflict);
//        Solver solver(5, solvable5, LinearConflict);
//        Solver solver(6, solvable6, LinearConflict);
//        Solver solver(7, solvable7, LinearConflict);
        solver.search();
    } catch (std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

//    try {
//        Solver solver(3, {8, 5, 2, 1, 7, 3, 0, 6, 4}, ManhattanDistance);
//    } catch (std::exception & e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }

	return (0);
}
