#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool isInRange(int a, int b);
bool isDecreasing(const std::vector<int>& report, int ignoreCount);
bool isIncreasing(const std::vector<int>& report, int ignoreCount);

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Cannot open the file: input.txt" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> reports = {};
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> report;
        int num;
        while (iss >> num) {
            report.push_back(num);
        }
        reports.push_back(report);
    }
    file.close();

    int safeCount = 0;
    for (const auto& report : reports) {
        bool isSafe = isDecreasing(report, 0) || isIncreasing(report, 0);

        if (isSafe) {
            safeCount++;
        }
    }

    std::cout << "Safe Count: " << safeCount << std::endl;
}

bool isInRange(int a, int b) {
    int diff = std::abs(a - b);
    return diff > 0 && diff <= 3;
}

bool isDecreasing(const std::vector<int>& report, int ignoreCount) {
    for (int i = 0, j = 1; i < report.size() - 1; i++, j++) {
        if (report[i] > report[j] || !isInRange(report[i], report[j])) {
            if (ignoreCount == 1) {
                return false;
            }
            else {
                std::vector<int> noI = copyWithoutIndex(report, i);
                std::vector<int> noJ = copyWithoutIndex(report, j);
                return isDecreasing(noI, 1) || isDecreasing(noJ, 1);
            }
        }
    }

    return true;
}

bool isIncreasing(const std::vector<int>& report, int ignoreCount) {
    for (int i = 0, j = 1; i < report.size() - 1; i++, j++) {
        if (report[i] < report[j] || !isInRange(report[i], report[j])) {
            if (ignoreCount == 1) {
                return false;
            }
            else {
                std::vector<int> noI = copyWithoutIndex(report, i);
                std::vector<int> noJ = copyWithoutIndex(report, j);
                return isIncreasing(noI, 1) || isIncreasing(noJ, 1);
            }
        }
    }

    return true;
}

const std::vector<int> copyWithoutIndex(const std::vector<int>& report, size_t index) {
    std::vector<int> copy;
    for (int i = 0; i < report.size(); i++) {
        if (i != index) {
            copy.push_back(report[i]);
        }
    }
    return copy;
}