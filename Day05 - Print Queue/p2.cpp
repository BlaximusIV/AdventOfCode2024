#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> parseLine(std::string line);
bool isValidOrder(const std::vector<int> &numbers,
                  std::map<int, std::vector<int>> &rules);
std::vector<int> correctOrder(std::vector<int> &numbers,
                              std::map<int, std::vector<int>> &rules);
int findIndex(int target, std::vector<int> v);

int main() {
  std::map<int, std::vector<int>> rules;
  int total = 0;

  std::ifstream file("input.txt");
  std::string line;
  bool parsingTop = true;
  while (getline(file, line)) {
    std::istringstream iss(line);
    if (line.empty()) {
      parsingTop = false;
      continue;
    }

    if (parsingTop) {
      size_t splitIndex = line.find("|");
      std::string rule = line.substr(0, splitIndex);
      std::string ruleNum = line.substr(splitIndex + 1);

      int ruleKey = std::stoi(rule);
      int ruleValue = std::stoi(ruleNum);
      if (rules.find(ruleKey) != rules.end()) {
        rules[ruleKey].push_back(ruleValue);
      } else {
        rules[ruleKey] = std::vector<int>{ruleValue};
      }
    } else {
      std::vector<int> numbers = parseLine(line);

      if (!isValidOrder(numbers, rules)) {
        // Get the valid order
        std::vector<int> orderedNumbers = correctOrder(numbers, rules);

        int index = (orderedNumbers.size() / 2);
        total += orderedNumbers[index];
      }
    }
  }

  std::cout << "Total: " << total << std::endl;
}

std::vector<int> parseLine(std::string line) {
  std::vector<int> result;

  std::string holder;
  for (auto c : line) {
    if (c == ',') {
      int num = std::stoi(holder);
      result.push_back(num);

      holder = "";
      continue;
    }

    holder += c;
  }

  result.push_back(std::stoi(holder));
  return result;
}

bool isValidOrder(const std::vector<int> &numbers,
                  std::map<int, std::vector<int>> &rules) {
  std::set<int> visited;

  for (auto num : numbers) {
    for (auto rule : rules[num]) {
      if (visited.find(rule) != visited.end()) {
        return false;
      }
    }

    visited.insert(num);
  }

  return true;
}

std::vector<int> correctOrder(std::vector<int> &numbers,
                              std::map<int, std::vector<int>> &rules) {
  bool corrected = false;
  while (!corrected) {

    std::set<int> visited;
    for (int i = 0; i < numbers.size(); i++) {
      std::vector<int> r = rules[numbers[i]];
      for (int j = 0 ; j < r.size(); j++) {
        if (visited.find(r[j]) != visited.end()) {
          // push number to end of &numbers
          int index = findIndex(r[j], numbers);

          int val = numbers[index];
          numbers.erase(numbers.begin() + index);
          numbers.push_back(val);
          
          // break out and try again
          i = numbers.size();
          break;
        }
      }

      if (i == numbers.size() - 1) {
          corrected = true;
      }

      visited.insert(numbers[i]);
    }
  }

  return numbers;
}

int findIndex(int target, std::vector<int> v) {
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == target) {
      return i;
    }
  }

  return -1;
}
