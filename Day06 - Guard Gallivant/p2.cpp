#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>

enum Direction
{
    North,
    East,
    South,
    West
};

struct Guard
{
    // row
    int r;
    // column
    int c;
    // Direction
    Direction d;
};

bool isOutOfBounds(const int r, const int c, const std::vector<std::vector<char>> &map);
Guard findGuard(const std::vector<std::vector<char>> &map);
bool isInfiniteRoute(Guard& g, const int r, const int c, const std::vector<std::vector<char>> &map);
void visit(Guard &g, std::map<int, std::map<int, std::set<Direction>>> &visited);
bool isVisitedInDirection(const Guard& g, std::map<int, std::map<int, std::set<Direction>>>& visited);

// A hacky, brute-force solution to today's problem
// If I refactor it, I want to try a more elegant algorithm for determining whether there is a cycle
// Perhaps don't do it one space at a time, but do something like "raytracing"
int main()
{
    std::vector<std::vector<char>> map = {};

    std::ifstream file("input.txt");
    std::string line;
    while (getline(file, line))
    {
        std::vector<char> vec(line.begin(), line.end());
        map.push_back(vec);
    }

    Guard startGuard = findGuard(map);

    int infiniteRouteCount = 0;
    for (int r = 0; r < map.size(); r++) {
        for (int c = 0; c < map[0].size(); c++) {
            if (map[r][c] == '#') {
                continue;
            }

            std::cout << "Checking for: " << r << "," << c << std::endl;

            Guard g = Guard {startGuard.r, startGuard.c, startGuard.d };
            if (isInfiniteRoute(g, r, c, map)) {
                infiniteRouteCount++;
            }
        }
    }

    std::cout << "Infinite Route Count: " << infiniteRouteCount << std::endl;
}

bool isOutOfBounds(const int r, const int c, const std::vector<std::vector<char>> &map)
{
    if (r >= map.size() || r < 0 || c >= map[0].size() || c < 0)
    {
        return true;
    }

    return false;
}

Guard findGuard(const std::vector<std::vector<char>> &map)
{
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            char c = map[i][j];
            if (c != '.' && c != '#')
            {
                Guard g = Guard{i, j, Direction::North};
                return g;
            }
        }
    }

    return Guard{};
}

std::pair<int, int> getNextPosition(const Guard &g)
{
    std::pair<int, int> coords = std::make_pair(g.r, g.c);

    coords.first += g.d == Direction::North   ? -1
                    : g.d == Direction::South ? 1
                                              : 0;

    coords.second += g.d == Direction::East   ? 1
                     : g.d == Direction::West ? -1
                                              : 0;

    return coords;
}

void rotateGuard(Guard &g)
{
    g.d = g.d == Direction::North   ? Direction::East
          : g.d == Direction::East  ? Direction::South
          : g.d == Direction::South ? Direction::West
                                    : Direction::North;
}

void visit(Guard &g, std::map<int, std::map<int, std::set<Direction>>> &visited)
{
    if (visited.find(g.r) == visited.end())
    {
        visited[g.r] = {};
    }

    if (visited[g.r].find(g.c) == visited[g.r].end()) {
        visited[g.r][g.c] = {};
    }

    visited[g.r][g.c].insert(g.d);
}

bool isVisitedInDirection(const Guard& g, std::map<int, std::map<int, std::set<Direction>>>& visited) {
    if (visited.find(g.r) != visited.end()) {
            if (visited[g.r].find(g.c) != visited[g.r].end()) {
                if (visited[g.r][g.c].find(g.d) != visited[g.r][g.c].end()) {
                    return true;
                }
            }
        }

    return false;
}

bool isInfiniteRoute(Guard& g, const int r, const int c, const std::vector<std::vector<char>> &map)
{
    std::map<int, std::map<int, std::set<Direction>>> visited;
    visit(g, visited);
    int rows = map.size();
    int cols = map[0].size();

    while (g.r < rows && g.c < cols)
    {
        std::pair<int, int> next = getNextPosition(g);
        
        // If you can move there, move there. Update visited if in bounds
        if (!isOutOfBounds(next.first, next.second, map))
        {
            if (map[next.first][next.second] == '#' || (next.first == r && next.second == c))
            {
                rotateGuard(g);
            }
            else
            {
                g.r = next.first;
                g.c = next.second;

                // If we've already visited this spot in the same direction, we're in a loop
                if (isVisitedInDirection(g, visited)) {
                    return true;
                }

                visit(g, visited);
            }
        }
        else
        {
            return false;
        }
    }

    return false;
}
