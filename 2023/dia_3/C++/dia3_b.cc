// --- Part Two ---
// The engineer finds the missing part and installs it in the engine! As the engine springs to life, you jump in the closest gondola, finally ready to ascend to the water source.

// You don't seem to be going very fast, though. Maybe something is still wrong? Fortunately, the gondola has a phone labeled "help", so you pick it up and the engineer answers.

// Before you can explain the situation, she suggests that you look out the window. There stands the engineer, holding a phone in one hand and waving with the other. You're going so slowly that you haven't even left the station. You exit the gondola.

// The missing part wasn't the only issue - one of the gears in the engine is wrong. A gear is any * symbol that is adjacent to exactly two part numbers. Its gear ratio is the result of multiplying those two numbers together.

// This time, you need to find the gear ratio of every gear and add them all up so that the engineer can figure out which gear needs to be replaced.

// Consider the same engine schematic again:

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
// In this schematic, there are two gears. The first is in the top left; it has part numbers 467 and 35, so its gear ratio is 16345. The second gear is in the lower right; its gear ratio is 451490. (The * adjacent to 617 is not a gear because it is only adjacent to one part number.) Adding up all of the gear ratios produces 467835.

// What is the sum of all of the gear ratios in your engine schematic?

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

struct Number {
  int gear_id;
  int value;
};

struct Gear {
  int gear_id;
  std::pair <int, int> coords;
};

void CheckGears(const char matrix[10][10], int row, const std::vector<int>& indexes, std::vector<Gear>& gears, const std::string& number, std::vector<Number>& numbers) {
  if (row < 0 || row > 9) {
    return;
  }
  int gear_counter{0};
  for (int i{0}; i < indexes.size(); ++i) {

    std::vector<char> row_vector;
    for (int j{0}; j < 10; ++j) {
      row_vector.emplace_back(matrix[row][j]);
    }

    for (int j{0}; j < row_vector.size(); ++j) {
      if (row_vector[j] == '*') {
        bool crear_gear{true};
        for (Gear& gear : gears) {
          std::cout << gear.coords.first << " " << gear.coords.second << std::endl;
          if (gear.coords.first == row && gear.coords.second == j) {
            Number new_number;
            new_number.gear_id = gear.gear_id;
            new_number.value = std::stoi(number);
            crear_gear = false;
          }
        }
        if (crear_gear) {
          std::cout << "Gear Counter: " << gear_counter << std::endl;
          Gear new_gear;
          new_gear.gear_id = gear_counter;
          new_gear.coords.first = row;
          new_gear.coords.second = j;
          gears.emplace_back(new_gear);
          Number new_number;
          new_number.gear_id = gear_counter;
          new_number.value = std::stoi(number);
          numbers.emplace_back(new_number);
          gear_counter++;
        }
      }
    }
  }
}

int main() {
  std::ifstream file{"input/input2.txt", std::ios_base::in};
  std::string line;
  char matrix[10][10];
  // Crear matrix
  for (int i{0}; i < 10; ++i) {
    getline(file, line);
    for (int j{0}; j < line.size(); ++j) {
      matrix[i][j] = line[j];
    }
  }
  // Comprobar gears
  const char gear{'*'};
  unsigned long sum{0};
  std::vector<Gear> gears;
  std::vector<Number> numbers;
  for (int i{0}; i < 10; ++i) {
    std::vector<int> indexes;
    std::string number;
    for (int j{0}; j < 10; ++j) {
      if (isdigit(matrix[i][j])) {
        number += matrix[i][j];
        indexes.emplace_back(j);
      } else if (number != "") {
        CheckGears(matrix, i, indexes, gears, number, numbers);
        CheckGears(matrix, i - 1, indexes, gears, number, numbers);
        CheckGears(matrix, i + 1, indexes, gears, number, numbers);
        number = "";
        indexes.clear();
      }
    }
  }
  // Calcular sum
  for (Gear& gear : gears) {
    std::cout << "Gear: " << gear.gear_id << " " << gear.coords.first << " " << gear.coords.second << std::endl;
    for (Number& number : numbers) {
      std::cout << "Number: " << number.gear_id << " " << number.value << std::endl;
      for (Number& number2 : numbers) {
        std::cout << "Number2: " << number2.gear_id << " " << number2.value << std::endl;
        if (number.gear_id == number2.gear_id) {
          std::cout << "Sum: " << number.value * number2.value << std::endl;
          sum += number.value * number2.value;
        }
      }
    }
  }
  std::cout << sum << std::endl;
}