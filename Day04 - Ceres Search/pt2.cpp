#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int findXmasCount(std::vector<std::vector<char>>& puzzle);
bool isMas(std::string s);

int main () {
    std::vector<std::vector<char>> puzzle = {};

    std::ifstream file("input.txt");
    std::string line;
    while (getline(file, line)) {
        std::vector<char> vec(line.begin(), line.end());
        puzzle.push_back(vec);
    }
    file.close();

    int totalCount = findXmasCount(puzzle);

    std::cout << "Total matches: " << totalCount << std::endl;
}

int findXmasCount(std::vector<std::vector<char>>& puzzle) {
    int rCount = puzzle.size();
    int cCount = puzzle[0].size();
    int totalCount = 0;
    for (int i = 1; i < rCount - 1; i++) {
        for (int j = 1; j < cCount -1; j++) {
            std::string matchOne = std::string() + puzzle[i - 1][j - 1] + puzzle[i][j] + puzzle[i + 1][j + 1];
            std::string matchTwo = std::string() + puzzle[i - 1][j + 1] + puzzle[i][j] + puzzle[i + 1][j - 1];

            if (isMas(matchOne) && isMas(matchTwo)) {
                totalCount++;
            }
        }
    }
    return totalCount;
}

bool isMas(std::string s) {
    return s == "MAS" || s == "SAM";
}
