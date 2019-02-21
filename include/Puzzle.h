
#ifndef PUZZLE_H
#define PUZZLE_H

#include <cstddef>
#include <vector>
#include <iostream>
#include <sstream>

class Puzzle {

public:

    typedef int (*heuristic)(Puzzle const &, Puzzle const &);
    enum direction { UP, DOWN, LEFT, RIGHT };

    Puzzle(void);
    Puzzle(std::size_t size, std::vector<std::size_t> const & tiles);
    Puzzle(Puzzle const & target);
    Puzzle(Puzzle const & target, int direction);
    ~Puzzle(void);

    void init(std::size_t size, std::vector<std::size_t> const & tiles);

    bool isSolvable(void) const ;
    void updateScore(heuristic f, Puzzle const & goal);
    std::vector<Puzzle *> expand(void);

    std::string graph(void) const;

    Puzzle & operator = (Puzzle const & target);
    bool     operator == (Puzzle const & target) const ;

    std::vector<std::size_t> tiles;
    std::size_t size;
    Puzzle      *parent;

    std::size_t g;  // cost
    std::size_t h;  // heuristic
    std::size_t f;  // score = cost + heuristic

private:
    bool check_tiles(void) const ;
    void move(int direction);
};

std::ostream & operator << (std::ostream & out, const Puzzle & rhs);

#endif
