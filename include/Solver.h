
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

    typedef Puzzle::heuristic heuristic;

    Solver(int size, std::vector<std::size_t> tiles, Puzzle::heuristic f, std::size_t cost = 0);
    ~Solver(void);

    void search(void);
    std::string report(void) const;
    std::string graph(void) const;

    // h(x)
    static bool CheckParity(Puzzle const & p1, Puzzle const & p2);
    static int  MisplacedTiles(Puzzle const & p1, Puzzle const & p2);
    static int  ManhattanDistance(Puzzle const & p1, Puzzle const & p2);
    static int  LinearConflict(Puzzle const & p1, Puzzle const & p2);
    static int  Mixed(Puzzle const & p1, Puzzle const & p2);

private:

    struct compare_score {
        bool operator() (Puzzle const *p1, Puzzle const *p2) const { return (p1->f >= p2->f); }
    };

    std::vector<std::size_t> generate_solved_map(int size);
    std::size_t hash(Puzzle const &);
    void discover_node(Puzzle const &);
    std::string graph_node_view(Puzzle const & p, bool closed) const ;
    std::string graph_node_connection(Puzzle const & p) const ;

    Puzzle *initial;
    Puzzle *goal;

    Puzzle::heuristic const h;
    std::size_t const cost; // g(x)

    std::priority_queue<Puzzle *, std::vector<Puzzle *>, compare_score> open_queue;
    std::map<std::size_t, Puzzle *> open_list;
    std::map<std::size_t, Puzzle *> closed_list;
    std::size_t time_complexity;
    std::size_t size_complexity;

};

#endif
