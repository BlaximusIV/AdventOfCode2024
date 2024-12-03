#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

int main () {
    long long total = 0;
    std::ifstream file("input.txt");
    std::string line;
    std::regex mul("mul\\(\\d{1,3},\\d{1,3}\\)|do\\(\\)|don\'t\\(\\)");
    std::regex num("\\d{1,3}");
    bool multiply = true;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::sregex_iterator next(line.begin(), line.end(), mul);

        // parse integers from the regex, multiply them, and add them to a total
        while (next != std::sregex_iterator()) {
            std::smatch match = *next;
            std::string match_str = match.str();
            next++;

            if (match_str == "do()") {
                multiply = true;
                continue;
            } else if (match_str == "don't()") {
                multiply = false;
                continue;
            }

            if (multiply) {
                std::sregex_iterator num_next(match_str.begin(), match_str.end(), num);
                int product = 1;
                while (num_next != std::sregex_iterator()) {
                    std::smatch num_match = *num_next;
                    std::string num_str = num_match.str();
                    
                    // convert the string to an integer
                    int num = std::stoi(num_str);
                    product *= num;

                    num_next++;
                }
                
                total += product;
            }
        }
    }
    file.close();


    std::cout << "Total: " << total << std::endl;
}