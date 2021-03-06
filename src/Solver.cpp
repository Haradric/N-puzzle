
#include "Solver.h"
#include <algorithm>
#include <list>
#include <memory>
#include <sstream>

Solver::Solver(int size, std::vector<std::size_t> const &tiles, Puzzle::heuristic f, std::size_t cost) : h(f), cost(cost), time_complexity(0), size_complexity(0) {

    std::unique_ptr<Puzzle> init_ptr(new Puzzle(size, tiles));
    std::unique_ptr<Puzzle> goal_ptr(new Puzzle(size, generate_solved_map(size)));

    if (init_ptr.get()->isSolvable() != goal_ptr.get()->isSolvable())
        throw std::runtime_error("this puzzle is unsolvable");

    initial = init_ptr.release();
    goal    = goal_ptr.release();

    initial->updateScore(h, *goal);

    Puzzle *copy = new Puzzle(*initial);

    open.insert(std::pair<std::size_t, Puzzle *>(hash(*copy), copy));
    open_queue.push(copy);
    time_complexity++;
}

Solver::~Solver(void) {

    for (auto it = open.begin(); it != open.end(); it++)
        delete (*it).second;
    open.clear();

    for (auto it = closed.begin(); it != closed.end(); it++)
        delete (*it).second;
    closed.clear();

    delete initial;
    delete goal;
}

void Solver::search(void) {

    while (!open.empty()) {

        Puzzle *current = open_queue.top();

        if (current->tiles == goal->tiles) {
            *goal = *current;
            return ;
        }

        auto it = open.find(hash(*current));
        closed.insert(*it);
        open.erase(it);
        open_queue.pop();

        discover_node(*current);
        size_complexity = (open.size() > size_complexity) ? open.size() : size_complexity;
    }
    throw std::runtime_error("can't find solution");
}

void Solver::discover_node(Puzzle const &puzzle) {

    for (auto i = 0; i < Puzzle::DIRECTION_LAST; i++) {

        std::map<std::size_t, Puzzle *>::iterator it;
        std::unique_ptr<Puzzle> neighbor;
        std::size_t             hash;

        try {
            neighbor.reset(new Puzzle(puzzle.size, puzzle.expand(i)));
            neighbor->parent = const_cast<Puzzle *>(&puzzle);
            neighbor->g = puzzle.g + cost;
            neighbor->updateScore(h, *goal);
        } catch (...) {
            continue ;
        }

        hash = Solver::hash(*(neighbor.get()));

        it = closed.find(hash);
        if (it != closed.end())
            continue ;

        it = open.find(hash);
        if (it == open.end()) {
            open.insert(std::pair<std::size_t, Puzzle *>(hash, neighbor.get()));
            open_queue.push(neighbor.get());
            time_complexity++;
            neighbor.release();
        }
    }
}

std::string Solver::report(void) const {

    std::stringstream   ss;
    std::list<Puzzle *> states;

    states.push_front(goal);
    while (states.front()->parent != nullptr) {
        states.push_front(states.front()->parent);
    }

    for (auto it = states.begin(); it != states.end(); it++) {
        ss << **it << std::endl;
    }

    ss << "complexity in time: " << time_complexity << std::endl;
    ss << "complexity in size: " << size_complexity << std::endl;
    ss << "number of moves:    " << states.size() - 1 << std::endl;

    return (ss.str());
}

std::string Solver::graph_node_view(Puzzle const &p, bool closed) const {

    std::stringstream ss;
    std::stringstream dbg_info;

    //    dbg_info << "|{id: " << id << "|g : " << g << "|h : " << h << "|f : " << f << "}";
    for (auto it = p.tiles.begin(); it != p.tiles.end(); it++) {
        ss << *it;
    }

    ss << " [label = \"{";
    for (auto i = 0; i < p.size; i++) {
        ss << "{";
        for (auto j = 0; j < p.size; j++) {
            ss << p.tiles[j * p.size + i];
            if (j != p.size - 1)
                ss << "|";
        }
        ss << "}";
        if (i != p.size - 1)
            ss << "|";
    }

    ss << "}" << dbg_info.str() << "\"";
    if (closed)
        ss << ", style=filled";
    ss << "]";

    return (ss.str());
}

std::string Solver::graph_node_connection(Puzzle const &p) const {

    std::stringstream ss;

    if (!goal->parent)
        throw std::runtime_error("this puzzle is not solved yet");

    for (auto it = p.tiles.begin(); it != p.tiles.end(); it++) {
        ss << *it;
    }

    ss << " -> ";

    for (auto it = p.parent->tiles.begin(); it != p.parent->tiles.end(); it++) {
        ss << *it;
    }

    return (ss.str());
}

std::string Solver::graph(void) const {

    std::stringstream ss;

    if (!goal->parent)
        throw std::runtime_error("this puzzle is not solved yet");

    ss << "strict digraph G {" << std::endl;
    ss << "    rankdir=RL" << std::endl;
    ss << "    node [shape=Mrecord];" << std::endl;

    for (auto it = closed.begin(); it != closed.end(); it++) {
        ss << "    " << graph_node_view(*(it->second), 1) << std::endl;
    }

    for (auto it = open.begin(); it != open.end(); it++) {
        ss << "    " << graph_node_view(*(it->second), 0) << std::endl;
    }

    for (auto it = closed.begin(); it != closed.end(); it++) {
        if (it->second->parent)
            ss << "    " << graph_node_connection(*(it->second)) << std::endl;
    }

    for (auto it = open.begin(); it != open.end(); it++) {
        if (it->second->parent)
            ss << "    " << graph_node_connection(*(it->second)) << std::endl;
    }

    ss << "}" << std::endl;

    return (ss.str());
}

bool Solver::CheckParity(Puzzle const &puzzle, Puzzle const &goal) {

    return (puzzle.size == goal.size &&
            puzzle.isSolvable() == goal.isSolvable());
}

int  Solver::MisplacedTiles(Puzzle const &puzzle, Puzzle const &goal) {

    tiles_t const &t1 = puzzle.tiles;
    tiles_t const &t2 = goal.tiles;
    std::size_t sum = 0;

    if (puzzle.size != goal.size)
        return (-1);

    for (auto i = 0; i < t1.size(); i++) {
        if (t1[i] != t2[i])
            sum++;
    }

    return (sum);
}

int Solver::ManhattanDistance(Puzzle const &puzzle, Puzzle const &goal) {

    tiles_t const &t1 = puzzle.tiles;
    tiles_t const &t2 = goal.tiles;
    std::size_t size  = puzzle.size;
    std::size_t sum   = 0;

    if (puzzle.size != goal.size)
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

int  Solver::LinearConflict(Puzzle const &puzzle, Puzzle const &goal) {

    tiles_t const &t1 = puzzle.tiles;
    tiles_t const &t2 = goal.tiles;
    std::size_t   size    = puzzle.size;
    std::size_t   linear  = 0;

    if (puzzle.size != goal.size)
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

    return (ManhattanDistance(puzzle, goal) + 2 * linear);
}

int  Solver::Mixed(Puzzle const &puzzle, Puzzle const &goal) {

    return (MisplacedTiles(puzzle, goal) + LinearConflict(puzzle, goal));
}

Solver::tiles_t Solver::generate_solved_map(int size) {

    tiles_t tiles;
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

std::size_t Solver::hash(Puzzle const &puzzle) {

    std::size_t seed = puzzle.size;

    for(auto it = puzzle.tiles.begin(); it != puzzle.tiles.end(); it++) {
        seed ^= *it + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    return (seed);
}
