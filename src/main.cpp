
#include "InputParser.h"
#include "Solver.h"
#include "Puzzle.h"

#include <string>
#include <vector>
#include <iostream>

std::vector<std::size_t> solvable3 = {
    3, 8, 0,
    2, 4, 1,
    5, 7, 6,
};

std::vector<std::size_t> solvable4 = {
     1,  2,  8,  9,
     0, 13,  6,  5,
    12, 15, 10,  3,
     7, 11, 14,  4,
};

std::vector<std::size_t> solvable5 = {
    23,  9, 15,  6,  0,
    17, 19,  1, 21,  2,
    10, 14,  7, 18, 16,
     3, 11, 13,  5,  4,
    12, 20,  8, 24, 22,
};

std::vector<std::size_t> solvable6 = {
    25, 20, 14, 17, 35, 21,
    13, 11, 29, 23,  0,  5,
    33,  3,  4,  9, 27, 34,
    22, 10, 26, 24, 18, 19,
    32,  7, 16,  2, 12, 30,
    28, 31,  8,  6,  1, 15,
};

std::vector<std::size_t> solvable7 = {
    26, 38, 16, 43, 40,  1,  2,
     7,  9, 47, 32,  6, 46, 10,
    28, 36, 37, 31, 12, 35, 41,
    22, 29, 39, 44,  5, 15,  8,
     0, 24, 23, 18, 34, 27,  3,
    17, 19, 13, 42, 45, 30, 11,
    33,  4, 14, 21, 20, 48, 25,
};

std::vector<std::size_t> read_input(std::istream & is) {

    std::vector<size_t> nums;
    std::string         line;

    while (std::getline(is, line)) {
        if (line[0] == '#')
            continue ;

        auto it = line.begin();
        while (it != line.end() && (std::isspace(*it) || std::isdigit(*it))) {
            it++;
        }
        if (line.empty() || it != line.end())
            throw std::runtime_error("Invalid file format");

        std::stringstream ss(line);
        std::string       token;
        while (std::getline(ss, token, ' ')) {
            if (token == "")
                continue ;

            int n = std::atoi(token.c_str());
            if (n < 0)
                throw std::runtime_error("Invalid file format");
            nums.push_back(n);
        }
    }

    return (nums);
}

int main(int ac, const char **av) {

    std::string opt_str[] = {"input", "output"};
    InputParser config;

    config.register_option(InputParser::STRING, opt_str, sizeof(opt_str)/sizeof(*opt_str));
    config.read_args(ac, av);
//    std::cout << config << std::endl;

    try {
        std::vector<size_t> input = read_input(std::cin);
        std::vector<size_t> tiles(input.begin() + 1, input.end());
        std::size_t size = input.at(0);

//        std::cout << "input[" << input.size() << "] = { ";
//        for (auto it = input.begin(); it != input.end(); it++) {
//            std::cout << *it << " ";
//        }
//        std::cout << "};" << std::endl;

        Solver solver(size, tiles, Solver::LinearConflict);
        solver.search();
        std::cout << solver.report();
//        std::cout << solver.graph();

    } catch (std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return (0);
}
