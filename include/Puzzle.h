
#ifndef PUZZLE_H
#define PUZZLE_H

#include <cstddef>
#include <vector>
#include <iostream>
#include <sstream>

class Puzzle {

public:

    enum direction { UP, DOWN, LEFT, RIGHT };

    Puzzle(void);
    Puzzle(std::size_t size, std::vector<int> const & tiles);
    Puzzle(Puzzle const & target);
    Puzzle(Puzzle const & target, int direction);
    ~Puzzle(void);

    void init(std::size_t size, std::vector<int> const & tiles);

    bool isSolvable(void) const ;
    void updateScore(int (*heuristic)(Puzzle const &, Puzzle const &), Puzzle const & goal);
    std::vector<Puzzle *> expand(void);

    std::string graph(void) const;

    Puzzle & operator = (Puzzle const & target);
    bool     operator == (Puzzle const & target) const ;

    std::vector<int> get_tiles(void) const ;
    std::size_t      get_size(void) const ;
    std::size_t      get_score(void) const ;
    std::size_t      get_cost(void) const ;

private:
    std::size_t      size;
    std::vector<int> tiles;
    Puzzle           *parent;

    std::size_t g;  // cost
    std::size_t h;  // heuristic
    std::size_t f;  // score = cost + heuristic

    bool check_tiles(void) const ;
    void move(int direction);
};

bool CheckParity(Puzzle const & p1, Puzzle const & p2);
int  MisplacedTiles(Puzzle const & p1, Puzzle const & p2);
int  ManhattanDistance(Puzzle const & p1, Puzzle const & p2);
int  LinearConflict(Puzzle const & p1, Puzzle const & p2);

std::ostream & operator << (std::ostream & out, const Puzzle & rhs);

#endif
