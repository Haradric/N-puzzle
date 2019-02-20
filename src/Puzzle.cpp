
#include "Puzzle.h"
#include <algorithm>
#include <numeric>
#include <iomanip>

Puzzle::Puzzle(void) : size(0), parent(nullptr), g(0), h(0), f(0) {}

Puzzle::Puzzle(std::size_t size, std::vector<int> const & tiles) : parent(nullptr), g(0), h(0), f(0) {

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

void Puzzle::init(std::size_t size, std::vector<int> const & tiles) {

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

void Puzzle::updateScore(int (*f)(Puzzle const &, Puzzle const &), Puzzle const & goal) {

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

std::vector<int> Puzzle::get_tiles(void) const {

    return (this->tiles);
}

std::size_t Puzzle::get_size(void) const {

    return (this->size);
}

std::size_t Puzzle::get_score(void) const {

    return (this->f);
}

std::size_t Puzzle::get_cost(void) const {

    return (this->g);
}

bool Puzzle::check_tiles(void) const {

    std::vector<int> copy(tiles), sorted(size * size);

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

    return (p1.get_tiles() == p2.get_tiles());
}

bool CheckParity(Puzzle const & p1, Puzzle const & p2) {

    return (p1.get_size() == p2.get_size() &&
            p1.isSolvable() == p2.isSolvable());
}

int  MisplacedTiles(Puzzle const & p1, Puzzle const & p2) {

    std::vector<int> t1 = p1.get_tiles();
    std::vector<int> t2 = p2.get_tiles();
    std::size_t sum = 0;

    if (p1.get_size() != p2.get_size())
        return (-1);

    for (auto i = 0; i < t1.size(); i++) {
        if (t1[i] != t2[i])
            sum++;
    }

    return (sum);
}

int ManhattanDistance(Puzzle const & p1, Puzzle const & p2) {

    std::vector<int> t1 = p1.get_tiles();
    std::vector<int> t2 = p2.get_tiles();
    std::size_t size = p1.get_size();
    std::size_t sum  = 0;

    if (p1.get_size() != p2.get_size())
        return (-1);

    for (auto i = 0; i < t1.size(); i++) {

        if (t1[i] == 0)
            continue ;

        int j = std::distance(t2.begin(), std::find(t2.begin(), t2.end(), t1[i]));
        int x1 = i / size;
        int y1 = i % size;
        int x2 = j / size;
        int y2 = j % size;
        sum += abs(x1 - x2) + abs(y1 - y2);
    }

    return (sum);
}

int  LinearConflict(Puzzle const & p1, Puzzle const & p2) {

    std::vector<int> t1 = p1.get_tiles();
    std::vector<int> t2 = p2.get_tiles();
    std::size_t size    = p1.get_size();
    std::size_t linear  = 0;

    if (p1.get_size() != p2.get_size())
        return (-1);

    for (auto i = 0; i < t1.size(); i++) {

        if (t1[i] == 0)
            continue ;

        int i1 = std::distance(t2.begin(), std::find(t2.begin(), t2.end(), t1[i]));
        int x1 = i1 / size;
        int y1 = i1 % size;

        // for row
        for (auto k = i + 1; k % size != 0; k++) {

            if (t1[k] == 0)
                continue ;

            int i2 = std::distance(t2.begin(), std::find(t2.begin(), t2.end(), t1[k]));
            int x2 = i2 / size;
            int y2 = i2 % size;
            if (x1 == x2 && y1 > y2)
                linear++;
        }

        // for col
        for (auto k = i + size; k < t1.size(); k += size) {

            if (t1[k] == 0)
                continue ;

            int i2 = std::distance(t2.begin(), std::find(t2.begin(), t2.end(), t1[k]));
            int x2 = i2 / size;
            int y2 = i2 % size;
            if (x1 > x2 && y1 == y2)
                linear++;
        }
    }

    return (ManhattanDistance(p1, p2) + 2 * linear);
}

std::ostream & operator << (std::ostream & out, const Puzzle & rhs) {

    auto tiles = rhs.get_tiles();
    auto size  = rhs.get_size();
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
