
#ifndef SOLVER_H
#define SOLVER_H

#include "Puzzle.h"
#include <cstddef>
#include <vector>
#include <map>
#include <queue>
#include <memory>

class Solver {

public:

    Solver(int size, std::vector<std::size_t> tiles, Puzzle::heuristic f);
    ~Solver(void);

    void init(int size, std::vector<std::size_t> tiles, Puzzle::heuristic f);

    void search(void);

    std::string graph(void) const;

    // h(x)
    static bool CheckParity(Puzzle const & p1, Puzzle const & p2);
    static int  MisplacedTiles(Puzzle const & p1, Puzzle const & p2);
    static int  ManhattanDistance(Puzzle const & p1, Puzzle const & p2);
    static int  LinearConflict(Puzzle const & p1, Puzzle const & p2);

private:

    struct compare_score {
        bool operator() (Puzzle const *p1, Puzzle const *p2) const { return (p1->f >= p2->f); }
    };

    std::vector<std::size_t> generate_solved_map(int size);
    void discover_node(Puzzle const &);
    void report(void);

    Puzzle initial;
    Puzzle goal;

    Puzzle::heuristic const h;

    std::priority_queue<Puzzle *, std::vector<Puzzle *>, compare_score> open_queue;
    std::map<std::size_t, Puzzle *> open_list;
    std::map<std::size_t, Puzzle *> closed_list;

    Puzzle *solution;

};

#endif
