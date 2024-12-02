#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    vector<int> left = {};

    ifstream file("input.txt");

    map<int, int> rightMap = {};
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int a, b;
        iss >> a >> b;

        left.push_back(a);

        // Ensure value exists in map for later use
        if (rightMap.find(a) == rightMap.end()) {
            rightMap[a] = 0;
        }

        if (rightMap.find(b) == rightMap.end()) {
            rightMap[b] = 1;
        } else {
            rightMap[b] += 1;
        }
    }

    file.close();

    int total = 0;
    for (int i = 0; i < left.size(); i++) {
        total += left[i] * rightMap[left[i]];
    }

    cout << "Total Differences: " << total << endl;
}