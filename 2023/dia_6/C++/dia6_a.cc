// --- Part Two ---
// As the race is about to start, you realize the piece of paper with race times and record distances you got earlier actually just has very bad kerning. There's really only one race - ignore the spaces between the numbers on each line.

// So, the example from before:

// Time:      7  15   30
// Distance:  9  40  200
// ...now instead means this:

// Time:      71530
// Distance:  940200
// Now, you have to figure out how many ways there are to win this single race. In this example, the race lasts for 71530 milliseconds and the record distance you need to beat is 940200 millimeters. You could hold the button anywhere from 14 to 71516 milliseconds and beat the record, a total of 71503 ways!

// How many ways can you beat the record in this one much longer race?

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
  std::ifstream file("input/input2.txt");
  std::string line;
  std::vector<int> times;
  std::vector<int> distances;
  getline(file, line);
  std::string times_string = line.substr(line.find(":") + 1);
  // Parse times
  while (times_string.find(" ") != std::string::npos) {
    times.push_back(std::stoi(times_string.substr(0, times_string.find(" "))));
    times_string = times_string.substr(times_string.find(" ") + 1);
  }
  getline(file, line);
  std::string distances_string = line.substr(line.find(":") + 1);
  // Parse distances
  for (const auto time : times) {
    getline(file, line);
    distances.push_back(std::stoi(distances_string.substr(0, line.find(" "))));
    distances_string = distances_string.substr(distances_string.find(" ") + 1);
  }
  // Calculate
  int total{1};
  for (int i{0}; i < times.size(); ++i) {
    int distance{0};
    int counter{0}; 
    for (int j{0}; j <= times[i]; ++j) {
      distance = ((times[i] - j) * j);
      if (distance > distances[i]) {
        ++counter;
      }
    }
    total = counter * total;
  }
  std::cout << total << std::endl;
}