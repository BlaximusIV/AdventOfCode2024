#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

bool hasWord(const int r, const int c, const int index, const std::vector<int> direction, std::vector<std::vector<char>>& puzzle);
bool isInBounds(int r, int c, std::vector<std::vector<char>>& puzzle);
std::vector<std::vector<int>> directions();

int main () {
    std::vector<std::vector<char>> puzzle = {};

    std::ifstream file("input.txt");
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::vector<char> vec(line.begin(), line.end());
        puzzle.push_back(vec);
    }
    file.close();

    int totalCount = 0;
    for (int i = 0; i < puzzle.size(); i++) {
        for (int j = 0; j < puzzle[0].size(); j++) {
            if (puzzle[i][j] == 'X') {
                for (auto direction : directions()) {
                    if (hasWord(i, j, 0, direction, puzzle)) {
                        totalCount++;
                    }
                }
            }
        }
    }

    std::cout << "Total matches: " << totalCount << std::endl;
}

bool hasWord(
    const int r, 
    const int c, 
    const int index,
    const std::vector<int> direction,
    std::vector<std::vector<char>>& puzzle) {

    const std::string target = "XMAS";
    if(!isInBounds(r, c, puzzle)) {
        return false;
    }

    char targetChar = target[index];
    if (puzzle[r][c] != targetChar) {
        return false;
    }

    if (targetChar == 'S') {
        return true;
    }
    
    int nr = r + direction[0];
    int nc = c + direction[1];
    
    return hasWord(nr, nc, index + 1, direction, puzzle);
}

std::vector<std::vector<int>> directions() {
    return {
        {-1, 0},
        {-1, 1},
        {0, 1},
        {1, 1},
        {1, 0},
        {1, -1},
        {0, -1},
        {-1, -1}
    };
}

bool isInBounds(const int r, const int c, std::vector<std::vector<char>>& puzzle) {
    return r >= 0 && r < puzzle.size() && c >= 0 && c < puzzle[0].size();
}
