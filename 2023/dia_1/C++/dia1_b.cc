// Autor: Darío Fajardo

// --- Part Two ---
// Your calculation isn't quite right. It looks like some of the digits are actually spelled out with letters: one, two, three, four, five, six, seven, eight, and nine also count as valid "digits".

// Equipped with this new information, you now need to find the real first and last digit on each line. For example:

// two1nine
// eightwothree
// abcone2threexyz
// xtwone3four
// 4nineeightseven2
// zoneight234
// 7pqrstsixteen
// In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76. Adding these together produces 281.

// What is the sum of all of the calibration values?

#include <iostream>
#include <string>
#include <fstream>
#include <map>

int main() {
  std::map<std::string, int> conversion;
  conversion["one"] = 1;
  conversion["two"] = 2;  
  conversion["three"] = 3;
  conversion["four"] = 4;
  conversion["five"] = 5;
  conversion["six"] = 6;
  conversion["seven"] = 7;
  conversion["eight"] = 8;
  conversion["nine"] = 9;

  std::ifstream file("../input/input.txt", std::ios::in);
  std::string line;
  int sum{0};

  while (getline(file, line)) {
    std::string substring;
    std::string numbers;
    for (const auto& current_char : line) {
      if (isdigit(current_char)) {
        numbers += current_char;
        substring = "";
      } else {
        substring += current_char;
        for (const auto& pair : conversion) {
          if (substring.find(pair.first) != std::string::npos) {
            numbers += std::to_string(pair.second);
            substring = "";
            substring += current_char;
          }
        }
      }
    }
    int first{std::stoi(std::string{numbers[0]})};
    int last{std::stoi(std::string{numbers[numbers.size() - 1]})};
    sum += first * 10 + last;
  }
  std::cout << sum << "\n";
}