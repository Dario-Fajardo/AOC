// Autor: Darío Fajardo

// --- Part Two ---
// Everyone will starve if you only plant such a small number of seeds. Re-reading the almanac, it looks like the seeds: line actually describes ranges of seed numbers.

// The values on the initial seeds: line come in pairs. Within each pair, the first value is the start of the range and the second value is the length of the range. So, in the first line of the example above:

// seeds: 79 14 55 13
// This line describes two ranges of seed numbers to be planted in the garden. The first range starts with seed number 79 and contains 14 values: 79, 80, ..., 91, 92. The second range starts with seed number 55 and contains 13 values: 55, 56, ..., 66, 67.

// Now, rather than considering four seed numbers, you need to consider a total of 27 seed numbers.

// In the above example, the lowest location number can be obtained from seed number 82, which corresponds to soil 84, fertilizer 84, water 84, light 77, temperature 45, humidity 46, and location 46. So, the lowest location number is 46.

// Consider all of the initial seed numbers listed in the ranges on the first line of the almanac. What is the lowest location number that corresponds to any of the initial seed numbers?

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::ifstream file{"input/input.txt"};
    std::string line;
    std::vector<long> seeds;
    std::vector<long> minimums;
    std::vector<long> final_minimums;
    getline(file, line);
    std::string seeds_string{line.substr(line.find(":") + 2)};
    while (seeds_string.find(" ") != std::string::npos) {
        seeds.push_back(std::stol(seeds_string.substr(0, seeds_string.find(" "))));
        seeds_string = seeds_string.substr(seeds_string.find(" ") + 1);
    }
    seeds.push_back(std::stoi(seeds_string));
    while (line.find("seed-to-soil map") == std::string::npos) {
        getline(file, line);
    }
    for (long i{0}; i < seeds.size(); i += 2) {
        std::cout << "Rango " << i / 2 << " de " << (seeds.size() / 2) - 1 << "\n";
        for (long j{seeds[i]}, k{0}; j < seeds[i] + seeds[i + 1]; ++j, ++k) {
            std::cout << "semilla " << j << "\n";
            long seed{j};
            minimums.emplace_back(seed);
            getline(file, line);
            while (line.find(" ") != std::string::npos) {
                long destination{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                long source{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                long length{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                if (seed >= source && seed < source + length) {
                    seed = destination + seed - source;
                    break;
                }
                getline(file, line);
            }
            minimums[k] = seed;
            while (line.find("soil-to-fertilizer map") == std::string::npos) {
                getline(file, line);
            } 
            seed = minimums[k];
            getline(file, line);
            while (line.find(" ") != std::string::npos) {
                long destination{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                long source{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                long length{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                if (seed >= source && seed < source + length) {
                    seed = destination + seed - source;
                    break;
                }
            getline(file, line);
            }
            minimums[k] = seed;
            while (line.find("fertilizer-to-water map") == std::string::npos) {
                getline(file, line);
            }
            seed = minimums[k];
            getline(file, line);
            while (line.find(" ") != std::string::npos) {
                long destination{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                long source{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                long length{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                if (seed >= source && seed < source + length) {
                    seed = destination + seed - source;
                    break;
                }
                getline(file, line);
            }
            minimums[k] = seed;
            while (line.find("water-to-light map") == std::string::npos) {
                getline(file, line);
            }
            seed = minimums[k];
            getline(file, line);
            while (line.find(" ") != std::string::npos) {
                long destination{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                long source{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                long length{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                if (seed >= source && seed < source + length) {
                    seed = destination + seed - source;
                    break;
                }
                getline(file, line);
            }
            minimums[k] = seed;
            while (line.find("light-to-temperature map") == std::string::npos) {
                getline(file, line);
            }
            seed = minimums[k];
            getline(file, line);
            while (line.find(" ") != std::string::npos) {
                long destination{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                long source{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                long length{std::stol(line.substr(0, line.find(" ")))};
                line = line.substr(line.find(" ") + 1);
                if (seed >= source && seed < source + length) {
                    seed = destination + seed - source;
                    break;
                }
                getline(file, line);
            }
            minimums[k] = seed;
            while (line.find("temperature-to-humidity map") == std::string::npos) {
                getline(file, line);
            }
            seed = minimums[k];
            getline(file, line);
            while (line.find(" ") != std::string::npos) {
            long destination{std::stol(line.substr(0, line.find(" ")))};
            line = line.substr(line.find(" ") + 1);
            long source{std::stol(line.substr(0, line.find(" ")))};
            line = line.substr(line.find(" ") + 1);
            long length{std::stol(line.substr(0, line.find(" ")))};
            line = line.substr(line.find(" ") + 1);
            if (seed >= source && seed < source + length) {
                seed = destination + seed - source;
                break;
            }
                getline(file, line);
            }
            minimums[k] = seed;
            while (line.find("humidity-to-location map") == std::string::npos) {
                getline(file, line);
            }
            seed = minimums[k];
            getline(file, line);
            while (line != "end" && line.empty() == false) {
            long destination{std::stol(line.substr(0, line.find(" ")))};
            line = line.substr(line.find(" ") + 1);
            long source{std::stol(line.substr(0, line.find(" ")))};
            line = line.substr(line.find(" ") + 1);
            long length{std::stol(line.substr(0, line.find(" ")))};
            line = line.substr(line.find(" ") + 1);
            if (seed >= source && seed < source + length) {
                seed = destination + seed - source;
                break;
            }
            getline(file, line);
            }
            minimums[k] = seed;
            final_minimums.emplace_back(minimums[k]);
            file.seekg(0, std::ios::beg);
            getline(file, line);
            getline(file, line);
            getline(file, line);
        }
    }
    std::cout << "El mínimo es " << *std::min_element(final_minimums.begin(), final_minimums.end()) << "\n";
}