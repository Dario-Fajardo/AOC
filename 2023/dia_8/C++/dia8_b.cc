// Autor: Darío Fajardo

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <map>
#include <numeric>

long StepsToZ(const std::string& instructions, const std::map<std::string, std::pair<std::string, std::string>>& network, const std::string& key) {
  long steps = 0;
  std::string current_key{key};
  while (current_key[2] != 'Z') {
    for (const auto& instruction : instructions) {
      if (instruction == 'R') {
        current_key = network.at(current_key).second;
      } else if (instruction == 'L') {
        current_key = network.at(current_key).first;
      }
      steps++;
      if (current_key[2] == 'Z') {
        break;
      }
    }
  }
  return steps;
} 

int main() {
  std::ifstream file{"input/input.txt"};
  std::map<std::string, std::pair<std::string, std::string>> network;
  std::string line, instructions;
  std::vector<std::string> initial_keys;
  getline(file, line);
  instructions = line;
  getline(file, line);
  while (getline(file, line)) {
    std::string key{line.substr(0, line.find(' '))};
    std::string left{line.substr(line.find('(') + 1, line.find(',') - 7)};
    std::string right{line.substr(line.find(',') + 2, line.find(')') - 1)};
    right.erase(right.find(')'));
    if (key[2] == 'A') {
      initial_keys.push_back(key);
    }
    network[key] = std::make_pair(left, right);
  }
  std::vector<long> steps;
  for (const auto& key : initial_keys) {
    steps.emplace_back(StepsToZ(instructions, network, key));
  }
  long total = 1;
  for (const auto& step : steps) {
    total = std::lcm(total, step);
  }
  std::cout << total << std::endl;
}