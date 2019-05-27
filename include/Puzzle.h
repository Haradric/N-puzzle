
#ifndef PUZZLE_H
#define PUZZLE_H

#include <cstddef>
#include <iostream>
#include <sstream>
#include <vector>

class Puzzle {

public:

    typedef int (*heuristic)(Puzzle const &, Puzzle const &);
    typedef std::vector<std::size_t> tiles_t;
    enum direction { UP, DOWN, LEFT, RIGHT, DIRECTION_LAST };

    Puzzle(std::size_t size, tiles_t const &tiles);
    Puzzle(Puzzle const &);
    ~Puzzle(void);

    bool isSolvable(void) const ;
    void updateScore(heuristic f, Puzzle const &goal);

    tiles_t expand(int direction) const ;

    Puzzle &operator =  (Puzzle const &target);
    bool    operator == (Puzzle const &target) const ;

    tiles_t     const tiles;
    std::size_t const size;
    Puzzle            *parent;

    std::size_t id;
    std::size_t g;  // cost
    std::size_t h;  // heuristic
    std::size_t f;  // score = cost + heuristic

    static std::size_t inst;

private:

    bool check_tiles(void) const ;

};

std::ostream &operator << (std::ostream &out, const Puzzle &rhs);

#endif
