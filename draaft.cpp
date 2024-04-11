/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <queue>
#include <utility>
#include <algorithm> // for std::reverse

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            // Combine the hashes of the pair's elements
            size_t hash1 = hash<int>()(p.first);
            size_t hash2 = hash<int>()(p.second);
            return hash1 ^ (hash2 << 1);
        }
    };

    template <>
    struct equal_to<std::pair<int, int>> {
        bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }
    };
}

struct PathFinding
{
    template<typename T, typename priority_t>
    struct PriorityQueue
    {
        typedef std::pair<priority_t, T> PQElement;
        std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

        inline bool empty() const
        {
            return elements.empty();
        }

        inline void put(T item, priority_t priority)
        {
            elements.emplace(priority, item);
        }

        T get()
        {
            T best_item = elements.top().second;
            elements.pop();
            return best_item;
        }
    };

    //search neighbors function
    struct Neighbors
    {
        std::pair<int, int> above, bottom, left, right;
    };

    Neighbors neighborblocksSearch(int x, int y)
    {
        Neighbors neighbors;
        std::pair<int, int> BlockAbove;
        std::pair<int, int> BlockBottom;
        std::pair<int, int> BlockLeft;
        std::pair<int, int> BlockRight;


        BlockAbove.first = x;
        BlockAbove.second = y - 1;
        BlockBottom.first = x;
        BlockBottom.second = y + 1;
        BlockLeft.first = x - 1;
        BlockLeft.second = y;
        BlockRight.first = x + 1;
        BlockRight.second = y;

        neighbors.above = BlockAbove;
        neighbors.bottom = BlockBottom;
        neighbors.left = BlockLeft;
        neighbors.right = BlockRight;

        return neighbors;
    }
    //

    inline double heuristic(std::pair<int, int> a, std::pair<int, int> b)
    {
        return std::abs(a.first - b.first) + std::abs(a.second - b.second);
    }


    void a_star_search
    (
        std::pair<int, int> start,
        std::pair<int, int> goal,
        std::unordered_map<std::pair<int, int>, std::pair<int, int>>& came_from,
        std::unordered_map<std::pair<int, int>, double>& cost_so_far,
        std::string TerrainStatearray[13][13]
    )

    {

        PriorityQueue<std::pair<int, int>, double> frontier;
        frontier.put(start, 0);

        came_from[start] = start;
        cost_so_far[start] = 0;

        while (!frontier.empty())
        {
            std::pair<int, int> current = frontier.get();

            if (current == goal)
            {
                break;
            }

            //get which blocks are neighbors
            Neighbors neib = neighborblocksSearch(current.first, current.second);
            std::pair<int, int> neighbors[4];
            neighbors[0] = neib.above;
            neighbors[1] = neib.bottom;
            neighbors[2] = neib.left;
            neighbors[3] = neib.right;

            for (std::pair<int, int> next : neighbors)
            {
                if (static_cast<int>(next.first) <= 12 && static_cast<int>(next.first) >= 0
                    && static_cast<int>(next.second) <= 12 && static_cast<int>(next.second) >= 0
                    && TerrainStatearray[next.second][next.first]!="#")  
                {
                    double new_cost = cost_so_far[current] + std::stoi(TerrainStatearray[next.second][next.first]) + 1;
                    if (cost_so_far.find(next) == cost_so_far.end()
                        || new_cost < cost_so_far[next])
                    {
                        cost_so_far[next] = new_cost;
                        double priority = new_cost + heuristic(next, goal);
                        frontier.put(next, priority);
                        came_from[next] = current;
                    }
                }   
            }
        }
    }


    std::vector<std::pair<int, int>> returnPath
    (
        std::pair<int, int> start, std::pair<int, int> goal,
        std::unordered_map<std::pair<int, int>, std::pair<int, int>> came_from
    )
    {
        std::vector<std::pair<int, int>> path;
        std::pair<int, int> current = goal;
        if (came_from.find(goal) == came_from.end())
        {
            return path; // no path can be found
        }
        while (current != start)
        {
            path.push_back(current);
            current = came_from[current];
        }
        path.push_back(start); // optional
        std::reverse(path.begin(), path.end());
        return path;
    }

};

int main() {
    std::string TerrainStatearray[13][13] = {
        {"0", "0", "0", "#", "0", "#", "0", "#", "0", "0", "0", "0", "0"},
        {"#", "#", "0", "#", "0", "#", "0", "0", "0", "0", "0", "0", "0"},
        {"0", "0", "0", "#", "0", "#", "#", "0", "0", "0", "#", "0", "0"},
        {"0", "#", "#", "#", "0", "0", "#", "0", "#", "0", "#", "0", "0"},
        {"0", "0", "0", "9", "9", "#", "0", "0", "#", "0", "#", "0", "0"},
        {"#", "0", "#", "#", "9", "#", "0", "#", "0", "0", "#", "0", "0"},
        {"0", "0", "0", "#", "0", "#", "0", "#", "0", "0", "#", "0", "0"},
        {"0", "#", "0", "#", "0", "0", "0", "#", "#", "#", "#", "0", "0"},
        {"0", "0", "0", "#", "0", "#", "0", "0", "#", "0", "0", "0", "0"},
        {"0", "0", "0", "#", "0", "#", "0", "0", "#", "0", "0", "0", "0"},
        {"0", "0", "0", "#", "0", "#", "0", "0", "#", "0", "0", "0", "0"},
        {"0", "0", "0", "#", "0", "0", "0", "0", "#", "0", "0", "0", "0"},
        {"0", "0", "0", "0", "0", "#", "0", "0", "#", "0", "0", "0", "0"},
    };


    std::unordered_map<std::pair<int, int>, std::pair<int, int>> came_from;
    std::unordered_map<std::pair<int, int>, double> cost_so_far;
    PathFinding pf;
    std::pair<int, int> start = { 1, 0 };
    std::pair<int, int> goal = { 12,12 };
    pf.a_star_search(start, goal, came_from, cost_so_far, TerrainStatearray);

    std::cout << "Starting point: (" << start.first << ", " << start.second << ")" << std::endl;
    std::cout << "Destination: (" << goal.first << ", " << goal.second << ")" << std::endl;

    std::vector<std::pair<int, int>> path = pf.returnPath(start, goal, came_from);
    std::cout << "Path: ";
    std::cout << path.size()<<std::endl;
    for (auto point : path) {
        std::cout << "(" << point.first << ", " << point.second << ") ";
        TerrainStatearray[point.second][point.first] = " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 13; ++j) {
            std::cout << TerrainStatearray[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
*/