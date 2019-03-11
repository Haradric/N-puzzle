
#include "Solver.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

typedef struct {
    Solver::heuristic h = nullptr;
    std::size_t       cost = 0;
    std::size_t       graph = 0;
    std::string       file;
} conf_t;

static void usage(int exit_code) {

    std::cerr << "Usage: npuzzle [OPTIONS] [FILE]" << std::endl;
    std::cerr << std::endl;
    std::cerr << "Search:" << std::endl;
    std::cerr << "    -u, --uniform      uniform cost search" << std::endl;
    std::cerr << "    -g, --greedy       greedy search (default)" << std::endl;
    std::cerr << std::endl;
    std::cerr << "Heuristic:" << std::endl;
    std::cerr << "    -t, --misplaced    Misplaced Tiles" << std::endl;
    std::cerr << "    -d, --manhattan    Manhattan Distance" << std::endl;
    std::cerr << "    -l, --linear       Linear Conflict" << std::endl;
    std::cerr << "    -m, --mixed        Mixed (default)" << std::endl;
    std::cerr << std::endl;
    std::cerr << "Output:" << std::endl;
    std::cerr << "    -g, --graph        generate dot graph" << std::endl;
    exit(exit_code);
}

static std::vector<std::size_t> read_input(std::istream &is) {

    std::vector<size_t> nums;
    std::string         line;

    while (std::getline(is, line)) {

        if (line.empty())
            throw std::runtime_error("Invalid input format");

        auto pos = line.find('#');
        if (pos != std::string::npos)
            line.erase(line.begin() + pos, line.end());

        for (auto it = line.begin(); it != line.end(); it++) {
            if (!std::isspace(*it) && !std::isdigit(*it))
                throw std::runtime_error("Invalid input format");
        }

        std::stringstream ss(line);
        std::string       token;
        while (std::getline(ss, token, ' ')) {
            if (token == "")
                continue ;

            int n = std::atoi(token.c_str());
            if (n < 0)
                throw std::runtime_error("Invalid input format");
            nums.push_back(n);
        }
    }

    return (nums);
}

static conf_t read_arg(int ac, char const **av) {

    conf_t conf;

    conf.h = Solver::Mixed;

    for (auto i = 1; i < ac; i++) {
        std::string arg(av[i]);

        if (i + 1 == ac && arg[0] != '-')
            conf.file = arg;
        else if (arg == "-h" || arg == "--help")
            usage(0);
        else if (arg == "-u" || arg == "--uniform")
            conf.cost = 1;
        else if (arg == "-g" || arg == "--greedy")
            conf.cost = 0;
        else if (arg == "-t" || arg == "--misplaced")
            conf.h = Solver::MisplacedTiles;
        else if (arg == "-d" || arg == "--manhattan")
            conf.h = Solver::ManhattanDistance;
        else if (arg == "-l" || arg == "--linear")
            conf.h = Solver::LinearConflict;
        else if (arg == "-m" || arg == "--mixed")
            conf.h = Solver::Mixed;
        else if (arg == "-g" || arg == "--graph")
            conf.graph = 1;
        else
            throw std::runtime_error("illegal option: -- " + arg);
    }

    return (conf);
}

int main(int ac, char const **av) {

    try {

        conf_t conf = read_arg(ac, av);

        std::ifstream ifile(conf.file);
        std::vector<size_t> input;
        if (conf.file != "") {
            if (ifile)
                input = read_input(ifile);
            else
                throw std::runtime_error("can't read from " + conf.file);
        }
        else {
            input = read_input(std::cin);
        }

        std::vector<size_t> tiles(input.begin() + 1, input.end());
        std::size_t size = input.at(0);

        Solver solver(size, tiles, conf.h, conf.cost);
        solver.search();
        if (conf.graph)
            std::cout << solver.graph();
        else
            std::cout << solver.report();

    } catch (std::exception &e) {
        std::cerr << "npuzzle: error: " << e.what() << std::endl;
    }

    return (0);
}
