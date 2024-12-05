#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

std::vector<int> parseLine(std::string line);
bool isValidOrder(const std::vector<int>& numbers, std::map<int, std::vector<int>>& rules);

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
    }
    else {
      std::vector<int> numbers = parseLine(line);

      if (isValidOrder(numbers, rules)) {
        int index = (numbers.size() / 2);
        total += numbers[index];
      }
    }
  }

  std::cout << "Total: " << total << std::endl;
}

std::vector<int> parseLine(std::string line) {
  std::vector<int> result;

  std::string holder;
  for (auto c: line) {
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

bool isValidOrder(const std::vector<int>& numbers, std::map<int, std::vector<int>>& rules) {
  std::set<int> visited;

  for (auto num: numbers) {
    for (auto rule: rules[num]) {
      if (visited.find(rule) != visited.end()) {
        return false;
      }
    }

    visited.insert(num);
  }

  return true;
}
