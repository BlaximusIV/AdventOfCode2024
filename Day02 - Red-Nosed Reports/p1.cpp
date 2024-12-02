#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::vector<std::vector<int>> reports = {};

    std::ifstream file("input.txt");
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
    for (int i = 0; i < reports.size(); i++) {
        std::vector<int> report = reports[i];
        bool isIncreasing = report[0] < report[1];
        bool isSafe = true;
        for (int j = 0, k = 1; j < report.size() - 1; j++, k++) {
            int diff = std::abs(report[k] - report[j]);
            if (diff < 1 || diff > 3) {
                isSafe = false;
                break;
            }

            if (isIncreasing && report[j] >= report[k]) {
                isSafe = false;
                break;
            }

            else if (!isIncreasing && report[j] <= report[k]) {
                isSafe = false;
                break;
            }
        }

        if (isSafe) {
            safeCount++;
        }
    }

    std::cout << "Safe Count: " << safeCount << std::endl;
}