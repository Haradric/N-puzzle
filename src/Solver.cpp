
#include "Solver.h"

#include <list>
#include <algorithm>
#include <sstream>

Solver::Solver(int size, std::vector<std::size_t> tiles, Puzzle::heuristic f) : initial(size, tiles), goal(size, generate_solved_map(size)), h(f), solution(nullptr) {

    if (initial.isSolvable() != goal.isSolvable())
        throw std::runtime_error("this puzzle is unsolvable");

    Puzzle * copy = new Puzzle(initial.size, initial.tiles);
    copy->updateScore(h, goal);

    std::pair<std::size_t, Puzzle *> entry(Puzzle::hash(*copy), copy);
    open_list.insert(entry);
    open_queue.push(copy);
}

Solver::~Solver(void) {

    for (auto it = open_list.begin(); it != open_list.end(); it++)
        delete (*it).second;
    open_list.clear();

    for (auto it = closed_list.begin(); it != closed_list.end(); it++)
        delete (*it).second;
    closed_list.clear();
}

void Solver::search(void) {

    while (!open_list.empty()) {

        Puzzle *current = open_queue.top();
        if (current->tiles == goal.tiles) {
            solution = current;
            report();
            return ;
        }

        auto it = open_list.find(Puzzle::hash(*current));
        closed_list.insert(*it);
        open_list.erase(it);
        open_queue.pop();

        discover_node(*current);
    }
    throw std::runtime_error("can't find solution");
}

void Solver::discover_node(Puzzle const &puzzle) {

    for (auto i = 0; i < Puzzle::DIRECTION_LAST; i++) {

        std::map<std::size_t, Puzzle *>::iterator it;
        std::unique_ptr<Puzzle> neighbor;
        std::size_t             hash;

        try {
            neighbor.reset(new Puzzle(puzzle.size, puzzle.neighbor(i)));
            neighbor->parent = const_cast<Puzzle *>(&puzzle);
            neighbor->g = puzzle.g + 1;
            neighbor->updateScore(h, goal);
        } catch (...) {
            continue ;
        }

        hash = Puzzle::hash(*(neighbor.get()));

        it = closed_list.find(hash);
        if (it != closed_list.end())
            continue ;

        it = open_list.find(hash);
        if (it == open_list.end()) {
            open_list.insert(std::pair<std::size_t, Puzzle *>(hash, neighbor.get()));
            open_queue.push(neighbor.get());
            neighbor.release();
        }
    }
}

void Solver::report(void) {

//    if (solution == nullptr)
    std::list<Puzzle *> states;

    states.push_front(solution);
    while (states.front()->parent != nullptr) {
        states.push_front(states.front()->parent);
    }

    for (auto it = states.begin(); it != states.end(); it++) {
        std::cout << **it << std::endl;
    }

    std::cout << "complexity in time: " << std::endl; // ??
    std::cout << "complexity in size: " << std::endl; // ??
    std::cout << "number of moves:    " << states.size() - 1 << std::endl;

}

std::string Solver::graph(void) const {

    std::stringstream ss;

    ss << "strict digraph G {" << std::endl;

    for (auto it = open_list.begin(); it != open_list.end(); it++) {
        ss << "    " << it->second->graph(0) << std::endl;
    }

    for (auto it = closed_list.begin(); it != closed_list.end(); it++) {
        ss << "    " << it->second->graph(1) << std::endl;
    }

    ss << "}" << std::endl;

    return (ss.str());
}

bool Solver::CheckParity(Puzzle const & p1, Puzzle const & p2) {

    return (p1.size == p2.size &&
            p1.isSolvable() == p2.isSolvable());
}

int  Solver::MisplacedTiles(Puzzle const & p1, Puzzle const & p2) {

    std::vector<std::size_t> t1 = p1.tiles;
    std::vector<std::size_t> t2 = p2.tiles;
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

    std::vector<std::size_t> t1 = p1.tiles;
    std::vector<std::size_t> t2 = p2.tiles;
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

    std::vector<std::size_t> t1 = p1.tiles;
    std::vector<std::size_t> t2 = p2.tiles;
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

std::vector<std::size_t> Solver::generate_solved_map(int size) {

    std::vector<std::size_t> tiles;
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
