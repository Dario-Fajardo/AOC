// Autor: Darío Fajardo

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <map>

int main() {
  std::ifstream file{"input/input.txt"};
  std::map<std::string, std::pair<std::string, std::string>> network;
  std::string line, instructions;
  getline(file, line);
  instructions = line;
  getline(file, line);
  while (getline(file, line)) {
    std::string key{line.substr(0, line.find(' '))};
    std::string left{line.substr(line.find('(') + 1, line.find(',') - 7)};
    std::string right{line.substr(line.find(',') + 2, line.find(')') - 1)};
    right.erase(right.find(')'));
    network[key] = std::make_pair(left, right);
  }
  std::string current_key{"AAA"};
  int steps{0};
  while (current_key != "ZZZ") {
    for (const auto& instruction : instructions) {
      if (instruction == 'L') {
        current_key = network[current_key].first;
      } else if (instruction == 'R') {
        current_key = network[current_key].second;
      }
      ++steps;
      if (current_key == "ZZZ") {
        break;
      }
    }
  }
  std::cout << steps << std::endl;
}