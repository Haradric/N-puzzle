
#ifndef SOLVER_H
#define SOLVER_H

#include "Puzzle.h"
#include <cstddef>
#include <map>
#include <memory>
#include <queue>
#include <vector>

class Solver {

public:

    typedef Puzzle::heuristic heuristic;
    typedef Puzzle::tiles_t tiles_t;

    Solver(int size, std::vector<std::size_t> const &tiles, Puzzle::heuristic f, std::size_t cost = 0);
    ~Solver(void);

    void search(void);
    std::string report(void) const;
    std::string graph(void) const;

    // h(x)
    static bool CheckParity(Puzzle const &puzzle, Puzzle const &goal);
    static int  MisplacedTiles(Puzzle const &puzzle, Puzzle const &goal);
    static int  ManhattanDistance(Puzzle const &puzzle, Puzzle const &goal);
    static int  LinearConflict(Puzzle const &puzzle, Puzzle const &goal);
    static int  Mixed(Puzzle const &puzzle, Puzzle const &goal);

private:

    struct compare_score {
        bool operator() (Puzzle const *p1, Puzzle const *p2) const { return (p1->f >= p2->f); }
    };

    typedef std::priority_queue<Puzzle *, std::vector<Puzzle *>, compare_score> solver_pq;

    static tiles_t generate_solved_map(int size);
    static std::size_t hash(Puzzle const &);

    void discover_node(Puzzle const &);
    std::string graph_node_view(Puzzle const &p, bool closed) const ;
    std::string graph_node_connection(Puzzle const &p) const ;

    Puzzle *initial;
    Puzzle *goal;

    Puzzle::heuristic const h;
    std::size_t       const cost; // g(x)

    solver_pq open_queue;
    std::map<std::size_t, Puzzle *> open;
    std::map<std::size_t, Puzzle *> closed;
    std::size_t time_complexity;
    std::size_t size_complexity;

};

#endif
