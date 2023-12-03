// Autor: Darío Fajardo

// --- Day 3: Gear Ratios ---
// You and the Elf eventually reach a gondola lift station; he says the gondola lift will take you up to the water source, but this is as far as he can bring you. You go inside.

// It doesn't take long to find the gondolas, but there seems to be a problem: they're not moving.

// "Aaah!"

// You turn around to see a slightly-greasy Elf with a wrench and a look of surprise. "Sorry, I wasn't expecting anyone! The gondola lift isn't working right now; it'll still be a while before I can fix it." You offer to help.

// The engineer explains that an engine part seems to be missing from the engine, but nobody can figure out which one. If you can add up all the part numbers in the engine schematic, it should be easy to work out which part is missing.

// The engine schematic (your puzzle input) consists of a visual representation of the engine. There are lots of numbers and symbols you don't really understand, but apparently any number adjacent to a symbol, even diagonally, is a "part number" and should be included in your sum. (Periods (.) do not count as a symbol.)

// Here is an example engine schematic:

// 467..114..
// ...*......
// ..35..633.
// ......#...
// 617*......
// .....+.58.
// ..592.....
// ......755.
// ...$.*....
// .664.598..
// In this schematic, two numbers are not part numbers because they are not adjacent to a symbol: 114 (top right) and 58 (middle right). Every other number is adjacent to a symbol and so is a part number; their sum is 4361.

// Of course, the actual engine schematic is much larger. What is the sum of all of the part numbers in the engine schematic?

// for (int i{0}; i < 140; ++i) {
//   for (int j{0}; j < 140; ++j) {
//     std::cout << matrix[i][j];
//   }
//   std::cout << std::endl;
// }

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

bool CheckNumbers(const char matrix[140][140], int index, const std::vector<int>& indexes) {
  std::set<char> symbols{'+', '-', '*', '/', '&', '@', '#', '$', '%', '=', '^'};
  for (int i{0}; i < indexes.size(); ++i) {
    if (index != 139) {
      if (symbols.find(matrix[index][indexes[i] - 1]) != symbols.end() ||
      symbols.find(matrix[index][indexes[i] + 1]) != symbols.end() ||
      symbols.find(matrix[index - 1][indexes[i] - 1]) != symbols.end() ||
      symbols.find(matrix[index + 1][indexes[i] + 1]) != symbols.end() ||
      symbols.find(matrix[index + 1][indexes[i] - 1]) != symbols.end() ||
      symbols.find(matrix[index - 1][indexes[i] + 1]) != symbols.end() ||
      symbols.find(matrix[index - 1][indexes[i]]) != symbols.end() ||
      symbols.find(matrix[index + 1][indexes[i]]) != symbols.end()) {
        return true;
      }
    } else { // No mirar abajo
      if (symbols.find(matrix[index][indexes[i] - 1]) != symbols.end() ||
      symbols.find(matrix[index][indexes[i] + 1]) != symbols.end() ||
      symbols.find(matrix[index - 1][indexes[i] - 1]) != symbols.end() ||
      symbols.find(matrix[index - 1][indexes[i] + 1]) != symbols.end() ||
      symbols.find(matrix[index - 1][indexes[i]]) != symbols.end()) {
        return true;
      }
    }

  }
  return false;
}

int main() {
  std::ifstream file{"input/input.txt", std::ios_base::in};
  std::string line;
  char matrix[140][140];
  // Crear matrix
  for (int i{0}; i < 140; ++i) {
    getline(file, line);
    for (int j{0}; j < line.size(); ++j) {
      matrix[i][j] = line[j];
    }
  }
  // Comprobar numeros
  int sum{0};
  for (int i{0}; i < 140; ++i) {
    std::string number;
    std::vector<int> number_indexes;
    for (int j{0}; j < 140; ++j) {
      if (isdigit(matrix[i][j])) {
        number += matrix[i][j];
        number_indexes.emplace_back(j);
        if (j == 139) {
          if (CheckNumbers(matrix, i, number_indexes)) {
            sum += stoi(number);
          }
          number = "";
          number_indexes.clear();
        }
      } else {
        if (CheckNumbers(matrix, i, number_indexes)) {
          std::cout << number << std::endl;
          sum += stoi(number);
        }
        number = "";
        number_indexes.clear();
      }
    }
    number = "";
    number_indexes.clear();
  }
  std::cout << sum << std::endl;
  return 0;
}