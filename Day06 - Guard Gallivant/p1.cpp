#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>

enum Direction {
    North,
    East,
    South,
    West
};

struct Guard {
    // row
    int r;
    // column
    int c;
    // Direction
    Direction d;
};

bool isOutOfBounds(const int r, const int c, const std::vector<std::vector<char>>& map);
Guard findGuard(const std::vector<std::vector<char>>& map);
void simulateRoute(Guard& g, const std::vector<std::vector<char>>& map, std::map<int, std::set<int>>& visited);
void visit(Guard& g, std::map<int, std::set<int>>& visited);

int main() {
    std::vector<std::vector<char>> map = {};

    std::ifstream file("input.txt");
    std::string line;
    while(getline(file, line)) {
        std::vector<char> vec(line.begin(), line.end());
        map.push_back(vec);
    }

    std::map<int, std::set<int>> visited = {};
    Guard g = findGuard(map);
    visited[g.r] = std::set<int> {g.c};

    simulateRoute(g, map, visited);

    int visitCount = 0;
    for(auto it = visited.begin(); it != visited.end(); ++it) {
        visitCount += (it->second).size();
    }

    std::cout << "Visited Count: " << visitCount << std::endl;
}

bool isOutOfBounds(const int r, const int c, const std::vector<std::vector<char>>& map) {
    if (r >= map.size() || r < 0 || c >= map[0].size() || c < 0) {
        return true;
    }

    return false;
}

Guard findGuard(const std::vector<std::vector<char>>& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            char c = map[i][j];
            if (c != '.' && c != '#') {
                Guard g = Guard {i, j};

                if (c == '^') {
                    g.d = Direction::North;
                }
                else if (c == '>') {
                    g.d = Direction::East;
                }
                else if (c == 'v') {
                    g.d = Direction::South;
                }
                else {
                    g.d = Direction::West;
                }
                
                return g;
            }
        }
    }

    return Guard {};
}

std::pair<int, int> getNextPosition(const Guard& g) {
    std::pair<int, int> coords = std::make_pair(g.r, g.c);

    coords.first += g.d == Direction::North ? -1 
        : g.d == Direction::South ? 1
        : 0;

    coords.second += g.d == Direction::East ? 1
        : g.d == Direction::West ? -1
        : 0;
    
    return coords;
}

void rotateGuard(Guard& g) {
    g.d = g.d == Direction::North ? Direction::East
        : g.d == Direction::East ? Direction::South
        : g.d == Direction::South ? Direction::West
        : Direction::North;
}

void visit(Guard& g, std::map<int, std::set<int>>& visited) {
    if (visited.find(g.r) == visited.end()) {
        visited[g.r] = {};
    }

    visited[g.r].insert(g.c);
}

void simulateRoute(Guard& g, const std::vector<std::vector<char>>& map, std::map<int, std::set<int>>& visited) {
    int rows = map.size();
    int cols = map[0].size();

    while (g.r < rows && g.c < cols) {
        std::pair<int, int> next = getNextPosition(g);

        // If you can move there, move there. Update visited if in bounds
        if (!isOutOfBounds(next.first, next.second, map)) {
            if (map[next.first][next.second] == '#') {
                rotateGuard(g);
            }
            else {
                g.r = next.first;
                g.c = next.second;
                visit(g, visited);
            }
        }
        else {
            g.r = next.first;
            g.c = next.second;
        }
    }
}