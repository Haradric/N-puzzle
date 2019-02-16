
#ifndef PUZZLE_H
#define PUZZLE_H

#include <cstddef>
#include <vector>
#include <iostream>

class Puzzle {

public:
    Puzzle(void);
    Puzzle(std::size_t size, std::vector<int> const & tiles);
    Puzzle(Puzzle const & target);
    ~Puzzle(void);

    void init(std::size_t size, std::vector<int> const & tiles);

    bool isSolvable(void) const ;

    Puzzle & operator = (Puzzle const & target);
    bool     operator == (Puzzle const & target) const ;

    std::vector<int> get_tiles(void) const ;
    std::size_t      get_size(void) const ;

private:
    std::size_t      size;
    std::vector<int> tiles;

    int g, h, f;

    bool check_tiles(void) const ;

};

bool CheckParity(Puzzle const & p1, Puzzle const & p2);
int  MisplacedTiles(Puzzle const & p1, Puzzle const & p2);
int  ManhattanDistance(Puzzle const & p1, Puzzle const & p2);
int  LinearConflict(Puzzle const & p1, Puzzle const & p2);

std::ostream & operator << (std::ostream & out, const Puzzle & rhs);

#endif
