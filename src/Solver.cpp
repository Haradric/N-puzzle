
#include "Solver.h"

#include <algorithm>
#include <sstream>

Solver::Solver(void) {}

Solver::Solver(int size, std::vector<int> tiles, int (*h)(Puzzle const & p1, Puzzle const & p2)) {

    init(size, tiles, h);
}

Solver::~Solver(void) {

    for (auto it = open_list.begin(); it != open_list.end(); it++)
        delete *it;
    open_list.clear();

    for (auto it = closed_list.begin(); it != closed_list.end(); it++)
        delete *it;
    closed_list.clear();
}

void Solver::init(int size, std::vector<int> tiles, int (*h)(Puzzle const & p1, Puzzle const & p2)) {

    this->h = h;

    initial.init(size, tiles);
    goal.init(size, generate_solved_map(size));

    if (initial.isSolvable() != goal.isSolvable())
        throw std::runtime_error("this puzzle is unsolvable");

    Puzzle * copy = new Puzzle();
    (*copy) = initial;
    copy->updateScore(h, goal);

    open_list.insert(open_list.begin(), copy);
}

Puzzle const *Solver::search(void) {

    while (!open_list.empty()) {

//        std::cout << graph() << std::endl;
        auto best = std::min_element(open_list.begin(), open_list.end(), comp_f);// find_next_uc();
        if ((*best)->get_tiles() == goal.get_tiles()) {
            std::cout << graph() << std::endl;
            return (*best);
        }

        std::vector<Puzzle *> list = (*best)->expand();
        std::move(best, best + 1, std::back_inserter(closed_list));
        open_list.erase(best);
        for (auto it = list.begin(); it != list.end(); it++) {

            std::vector<Puzzle *>::iterator elem;

            (*it)->updateScore(h, goal);

            elem = std::find_if(closed_list.begin(), closed_list.end(), [&](Puzzle *p) { return ((*p).get_tiles() == (**it).get_tiles()); });
            if (elem != closed_list.end())
                continue ;

            elem = std::find_if(open_list.begin(), open_list.end(), [&](Puzzle *p) { return ((*p).get_tiles() == (**it).get_tiles()); });
            if (elem == open_list.end())
                open_list.push_back(*it);
            else if ((*it)->get_cost() < (*elem)->get_cost())
                **elem = **it;
        }
    }
    throw std::runtime_error("can't find solution");
}

std::string Solver::graph(void) const {

    std::stringstream ss;

    ss << "strict digraph G {" << std::endl;

    for (auto i = 0; i < open_list.size(); i++) {
        ss << "    " << open_list[i]->graph() << ";" << std::endl;
    }

    for (auto i = 0; i < closed_list.size(); i++) {
        ss << "    " << closed_list[i]->graph() << std::endl;
        ss << "    \"" << *(closed_list[i]) << "\" [style=filled];" << std::endl;
    }

    ss << "}" << std::endl;

    return (ss.str());
}

bool Solver::CheckParity(Puzzle const & p1, Puzzle const & p2) {

    return (p1.size == p2.size &&
            p1.isSolvable() == p2.isSolvable());
}

int  Solver::MisplacedTiles(Puzzle const & p1, Puzzle const & p2) {

    std::vector<int> t1 = p1.tiles;
    std::vector<int> t2 = p2.tiles;
    std::size_t sum = 0;

    if (p1.size != p2.size)
        return (-1);

    for (auto i = 0; i < t1.size(); i++) {
        if (t1[i] != t2[i])
            sum++;
    }

    return (sum);
}

int Solver::ManhattanDistance(Puzzle const & p1, Puzzle const & p2) {

    std::vector<int> t1 = p1.tiles;
    std::vector<int> t2 = p2.tiles;
    std::size_t size = p1.size;
    std::size_t sum  = 0;

    if (p1.size != p2.size)
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

int  Solver::LinearConflict(Puzzle const & p1, Puzzle const & p2) {

    std::vector<int> t1 = p1.tiles;
    std::vector<int> t2 = p2.tiles;
    std::size_t size    = p1.size;
    std::size_t linear  = 0;

    if (p1.size != p2.size)
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

std::vector<int> Solver::generate_solved_map(int size) {

    std::vector<int> tiles;
    int i = 0;    // first row
    int j = 0;    // first column
    int m = size; // last row
    int n = size; // last column
    int q = 0;

    tiles.resize(size * size);

    while (i < m && j < n) {

        for (int p = j; p < n; ++p)
            tiles[i * size + p] = ++q;
        i++;

        for (int p = i; p < m; ++p)
            tiles[p * size + n - 1] = ++q;
        n--;

        if (i < m) {
            for (int p = n - 1; p >= j; --p)
                tiles[(m - 1) * size + p] = ++q;
            m--;
        }

        if (j < n) {
            for (int p = m - 1; p >= i; --p)
                tiles[p * size + j] = ++q;
            j++;
        }
    }

    auto max = std::max_element(tiles.begin(), tiles.end());
    tiles[std::distance(tiles.begin(), max)] = 0;

    return (tiles);
}

bool  Solver::comp_f(Puzzle const *p1, Puzzle const *p2) {

    return (p1->get_score() < p2->get_score());
}

//Puzzle & Solver::find_next_uc(void) {
//
//    return (std::max_element(open_list.begin(), open_list.end(), comp_f));
//}
