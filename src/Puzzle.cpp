
#include "Puzzle.h"
#include <algorithm>
#include <numeric>
#include <iomanip>

std::size_t Puzzle::inst = 0;

Puzzle::Puzzle(std::size_t size, tiles_t const &tiles) : tiles(tiles), size(size), parent(nullptr), g(0), h(0), f(0) {

    if (size < 3)
        throw std::runtime_error("The size of the puzzle should be more than 3");

    if (tiles.size() != size * size || !check_tiles())
        throw std::runtime_error("Invalid input"); //

    id = inst++;
}

Puzzle::Puzzle(Puzzle const &target) : tiles(target.tiles), size(target.size) {

    (*this) = target;
    id = inst++;
}

Puzzle::~Puzzle(void) {}

bool Puzzle::isSolvable(void) const {

    auto inversions = 0;
    for (auto i = 0; i < tiles.size(); i++) {
        for (auto j = i + 1; j < tiles.size(); j++) {
            if (tiles[i] && tiles[j] && tiles[i] > tiles[j])
                inversions++;
        }
    }

    if (size & 1)
        return !(inversions & 1);

    auto row = std::distance(tiles.begin(), std::find(tiles.begin(), tiles.end(), 0)) / size + 1;
    if (row & 1)
        return !(inversions & 1);
    else
        return (inversions & 1);

}

void Puzzle::updateScore(heuristic f, Puzzle const &goal) {

    this->h = f(*this, goal);
    this->f = this->g + this->h;
}

Puzzle::tiles_t Puzzle::expand(int direction) const {

    tiles_t neighbor(tiles);
    int i_zero = std::distance(neighbor.begin(), std::find(neighbor.begin(), neighbor.end(), 0));
    int x_zero = i_zero / size;
    int y_zero = i_zero % size;
    int i_swap, x_swap, y_swap;

    switch (direction) {
        case UP:
            x_swap = x_zero + 1;
            y_swap = y_zero;
            break;
        case DOWN:
            x_swap = x_zero - 1;
            y_swap = y_zero;
            break;
        case LEFT:
            x_swap = x_zero;
            y_swap = y_zero + 1;
            break;
        case RIGHT:
            x_swap = x_zero;
            y_swap = y_zero - 1;
            break;
        default:
            throw std::runtime_error("wrong direction");
    }

    if (x_swap < 0 || x_swap >= size || y_swap < 0 || y_swap >= size)
        throw std::runtime_error("wrong direction");

    i_swap = x_swap * size + y_swap;
    std::swap(neighbor[i_zero], neighbor[i_swap]);

    return (neighbor);
}

Puzzle &Puzzle::operator = (Puzzle const &target) {

    parent = target.parent;
    g = target.g;
    h = target.h;
    f = target.f;

    return (*this);
}

bool Puzzle::operator == (Puzzle const &target) const {

    return (size   == target.size &&
            tiles  == target.tiles &&
            parent == target.parent &&
            g == target.g &&
            h == target.h &&
            f == target.f);
}

bool Puzzle::check_tiles(void) const {

    tiles_t copy(tiles), sorted(size * size);

    std::iota(sorted.begin(), sorted.end(), 0);
    std::sort(copy.begin(), copy.end());

    return (copy == sorted);
}

std::ostream &operator << (std::ostream &out, const Puzzle &rhs) {

    auto tiles = rhs.tiles;
    auto size  = rhs.size;
    auto width = std::to_string(size * size - 1).length();

    for (auto i = 0; i < tiles.size(); i++) {
        out << std::setw(width) << tiles[i];
        if ((i + 1) % size)
            out << " ";
        else
            out << std::endl;
    }

    return (out);
}
