#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> left = {};
    vector<int> right = {};

    ifstream file("input.txt");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int a, b;
        iss >> a >> b;

        left.push_back(a);
        right.push_back(b);
    }
    file.close();

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int total = 0;
    for (int i = 0; i < left.size(); i++) {
        int difference = abs(left[i] - right[i]);
        total += difference;
    }

    cout << "Total Difference: " << total << endl;
}
