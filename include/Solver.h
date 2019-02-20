
#ifndef SOLVER_H
#define SOLVER_H

#include "Puzzle.h"
#include <cstddef>
#include <vector>
#include <memory>

class Solver {

public:
    Solver(void);
    Solver(int size, std::vector<int> tiles, int (*h)(Puzzle const & p1, Puzzle const & p2));
    ~Solver(void);

    void init(int size, std::vector<int> tiles, int (*h)(Puzzle const & p1, Puzzle const & p2));

    Puzzle const *search(void);

    std::string graph(void) const;

private:
    Puzzle initial;
    Puzzle goal;

    int (*h)(Puzzle const & p1, Puzzle const & p2);

    std::vector<Puzzle *> open_list;
    std::vector<Puzzle *> closed_list;

    std::vector<int> generate_solved_map(int size);
    Puzzle & find_next_uc(void);
    static bool comp_f(Puzzle const *p1, Puzzle const *p2);
};

#endif
