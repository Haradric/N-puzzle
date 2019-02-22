
#ifndef SOLVER_H
#define SOLVER_H

#include "Puzzle.h"
#include <cstddef>
#include <vector>
#include <memory>

class Solver {

public:
    Solver(void);
    Solver(int size, std::vector<std::size_t> tiles, Puzzle::heuristic f);
    ~Solver(void);

    void init(int size, std::vector<std::size_t> tiles, Puzzle::heuristic f);

    Puzzle const *search(void);

    std::string graph(void) const;

    static bool CheckParity(Puzzle const & p1, Puzzle const & p2);
    static int  MisplacedTiles(Puzzle const & p1, Puzzle const & p2);
    static int  ManhattanDistance(Puzzle const & p1, Puzzle const & p2);
    static int  LinearConflict(Puzzle const & p1, Puzzle const & p2);

private:
    Puzzle initial;
    Puzzle goal;

    Puzzle::heuristic const h;

    std::vector<Puzzle *> open_list;
    std::vector<Puzzle *> closed_list;

    std::vector<std::size_t> generate_solved_map(int size);
    Puzzle & find_next_uc(void);
    static bool comp_f(Puzzle const *p1, Puzzle const *p2);
};

#endif
