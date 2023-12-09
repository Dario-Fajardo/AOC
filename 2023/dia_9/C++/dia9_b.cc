// Autor: Darío Fajardo

#include <iostream>
#include <fstream>
#include <vector>

bool CheckLevelZero(const std::vector<int>& level) {
  for (const auto& number : level) {
    if (number != 0) {
      return false;
    }
  }
  return true;
}

int main() {
  std::ifstream file{"input/input.txt", std::ios_base::in};
  std::string line;
  long total{0};
  while (std::getline(file, line)) {
    std::vector<int> line_numbers;
    while (line.size() > 0) {
      line_numbers.push_back(std::stoi(line.substr(0, line.find(' '))));
      line = line.substr(line.find(' ') + 1, line.size());
    }
    std::vector<std::vector<int>> levels;
    levels.push_back(line_numbers);
    while (!CheckLevelZero(levels.back())) {
      std::vector<int> next_level;
      for (int i{0}; i < levels.back().size() - 1; ++i) {
        next_level.push_back(levels.back()[i + 1] - levels.back()[i]);
      }
      levels.push_back(next_level);
    }
    int next_value{0};
    for (int i = levels.size() - 1; i >= 0; --i) {
      levels[i].emplace_back(levels[i].front() - next_value);
      next_value = levels[i].back();
    }
    total += levels[0].back();
  }
  std::cout << "Total: " << total << std::endl;
}