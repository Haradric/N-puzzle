
#ifndef SOLVER_H
#define SOLVER_H

#include "Puzzle.h"
#include <cstddef>
#include <vector>
#include <map>
#include <memory>

class Solver {

public:

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

    typedef std::pair<std::size_t, Puzzle *> solver_entry;

    Puzzle initial;
    Puzzle goal;

    Puzzle::heuristic const h;

    std::map<std::size_t, Puzzle *> open_list;
    std::map<std::size_t, Puzzle *> closed_list;

    std::vector<std::size_t> generate_solved_map(int size);
    void discover_node(Puzzle const &);
    static bool comp_f(solver_entry const &, solver_entry const &);
};

#endif
