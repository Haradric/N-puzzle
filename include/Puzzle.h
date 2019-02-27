
#ifndef PUZZLE_H
#define PUZZLE_H

#include <cstddef>
#include <vector>
#include <iostream>
#include <sstream>

class Puzzle {

public:

    typedef int (*heuristic)(Puzzle const &, Puzzle const &);
    enum direction { UP, DOWN, LEFT, RIGHT, DIRECTION_LAST };

    Puzzle(std::size_t size, std::vector<std::size_t> const & tiles);
    Puzzle(Puzzle const &);
    ~Puzzle(void);

    bool isSolvable(void) const ;
    void updateScore(heuristic f, Puzzle const & goal);

    std::string graph(void) const;
    std::vector<std::size_t> neighbor(int direction) const ;

    Puzzle & operator = (Puzzle const & target);
    bool     operator == (Puzzle const & target) const ;

    static std::size_t hash(Puzzle const &);

    std::vector<std::size_t> const tiles;
    std::size_t const size;
    Puzzle            *parent;

    std::size_t g;  // cost
    std::size_t h;  // heuristic
    std::size_t f;  // score = cost + heuristic

    std::size_t id;
    static std::size_t inst;

private:

    bool check_tiles(void) const ;
    void move(int direction);

};

std::ostream & operator << (std::ostream & out, const Puzzle & rhs);

#endif
