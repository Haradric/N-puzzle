
#include "Puzzle.h"
#include <algorithm>
#include <numeric>
#include <iomanip>

Puzzle::Puzzle(void) : size(0), parent(nullptr), g(0), h(0), f(0) {}

Puzzle::Puzzle(std::size_t size, std::vector<std::size_t> const & tiles) : parent(nullptr), g(0), h(0), f(0) {

    init(size, tiles);
}

Puzzle::Puzzle(Puzzle const & target) {

    (*this) = target;
}

Puzzle::Puzzle(Puzzle const & target, int direction) {

    (*this) = target;
    (*this).parent = const_cast<Puzzle *>(&target);
    (*this).g++;

    (*this).move(direction);
}

Puzzle::~Puzzle(void) {}

void Puzzle::init(std::size_t size, std::vector<std::size_t> const & tiles) {

    this->size  = size;
    this->tiles = tiles;

    if (size < 3)
        throw std::runtime_error("The size of the puzzle should be more than 3");

    if (tiles.size() != size * size || !check_tiles())
        throw std::runtime_error("Invalid input"); //
}

bool Puzzle::isSolvable(void) const {

    auto inversions = 0;
    for (std::size_t i = 0; i < tiles.size(); i++) {
        for (std::size_t j = i + 1; j < tiles.size(); j++) {
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

void Puzzle::updateScore(heuristic f, Puzzle const & goal) {

    this->h = f(*this, goal);
    this->f = this->g + this->h;
}

std::string Puzzle::graph(void) const {

    std::stringstream ss;

    ss << "\"";
    ss << *this;
    ss << "\"";

    if (!parent)
        return (ss.str());

    ss << " -> ";

    ss << "\"";
    ss << *parent;
    ss << "\"";

    return (ss.str());
}

Puzzle & Puzzle::operator = (Puzzle const & target) {

    size   = target.size;
    tiles  = target.tiles;
    parent = target.parent;
    g = target.g;
    h = target.h;
    f = target.f;

    return (*this);
}

bool Puzzle::operator == (Puzzle const & target) const {

    return (size   == target.size &&
            tiles  == target.tiles &&
            parent == target.parent &&
            g == target.g &&
            h == target.h &&
            f == target.f);
}

bool Puzzle::check_tiles(void) const {

    std::vector<std::size_t> copy(tiles), sorted(size * size);

    std::iota(sorted.begin(), sorted.end(), 0);
    std::sort(copy.begin(), copy.end());

    return (copy == sorted);
}

void Puzzle::move(int direction) {

    int i_zero = std::distance(tiles.begin(), std::find(tiles.begin(), tiles.end(), 0));
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
    std::swap(tiles[i_zero], tiles[i_swap]);
}

std::vector<Puzzle *> Puzzle::expand(void) {

    std::vector<Puzzle *> list;

    for (int i = UP; i <= RIGHT; i++) {
        try {
            Puzzle *elem = new Puzzle(*this, i);
            list.push_back(elem);
        } catch (...) {
            ;
        }
    }

    return (list);
}

bool compare(Puzzle const & p1, Puzzle const & p2) {

    return (p1.tiles == p2.tiles);
}

std::ostream & operator << (std::ostream & out, const Puzzle & rhs) {

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
