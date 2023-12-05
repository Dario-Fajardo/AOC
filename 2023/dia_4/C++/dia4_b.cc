// Autor: Darío Fajardo

// --- Part Two ---
// Just as you're about to report your findings to the Elf, one of you realizes that the rules have actually been printed on the back of every card this whole time.

// There's no such thing as "points". Instead, scratchcards only cause you to win more scratchcards equal to the number of winning numbers you have.

// Specifically, you win copies of the scratchcards below the winning card equal to the number of matches. So, if card 10 were to have 5 matching numbers, you would win one copy each of cards 11, 12, 13, 14, and 15.

// Copies of scratchcards are scored like normal scratchcards and have the same card number as the card they copied. So, if you win a copy of card 10 and it has 5 matching numbers, it would then win a copy of the same cards that the original card 10 won: cards 11, 12, 13, 14, and 15. This process repeats until none of the copies cause you to win any more cards. (Cards will never make you copy a card past the end of the table.)

// This time, the above example goes differently:

// Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
// Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
// Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
// Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
// Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
// Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11
// Card 1 has four matching numbers, so you win one copy each of the next four cards: cards 2, 3, 4, and 5.
// Your original card 2 has two matching numbers, so you win one copy each of cards 3 and 4.
// Your copy of card 2 also wins one copy each of cards 3 and 4.
// Your four instances of card 3 (one original and three copies) have two matching numbers, so you win four copies each of cards 4 and 5.
// Your eight instances of card 4 (one original and seven copies) have one matching number, so you win eight copies of card 5.
// Your fourteen instances of card 5 (one original and thirteen copies) have no matching numbers and win no more cards.
// Your one instance of card 6 (one original) has no matching numbers and wins no more cards.
// Once all of the originals and copies have been processed, you end up with 1 instance of card 1, 2 instances of card 2, 4 instances of card 3, 8 instances of card 4, 14 instances of card 5, and 1 instance of card 6. In total, this example pile of scratchcards causes you to ultimately have 30 scratchcards!

// Process all of the original and copied scratchcards until no more scratchcards are won. Including the original set of scratchcards, how many total scratchcards do you end up with?

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

int main() {
    std::ifstream file("input/input.txt", std::ios_base::in);
    std::string line;
    int total{0};
    std::map<int, int> points_line;
    std::map<int, int> ocurrencies_line;
    while (getline(file, line)) {
      std::string delimiter = "|";
      std::string game_number = line.substr(line.find("d") + 2, line.find(":") - 5);
      int game_number_int{std::stoi(game_number)};
      std::string winning_numbers = line.substr(line.find(":") + 1, line.find(delimiter) - 7);
      std::string my_numbers = line.substr(line.find(delimiter) + 1, line.length());
      std::vector<int> winning_numbers_vector;
      std::string number;
      int iterator{0};
      for (const auto& character : winning_numbers) {
        if (!isdigit(character) && number != "") {
          winning_numbers_vector.emplace_back(std::stoi(number));
          number = "";
        } else if (character != ' ' && character != '|') {
          number += character;
          if (iterator == winning_numbers.length() - 1) {
            winning_numbers_vector.emplace_back(std::stoi(number));
            number = "";
          }
        }
        ++iterator;
      }
      std::vector<int> my_numbers_vector;
      iterator = 0;
      for (const auto& character : my_numbers) {
        if (!isdigit(character) && number != "") {
          my_numbers_vector.emplace_back(std::stoi(number));
          number = "";
        } else if (character != ' ') {
          number += character;
          if (iterator == my_numbers.size() - 1) {
            my_numbers_vector.emplace_back(std::stoi(number));
            number = "";
          }
        }
        ++iterator;
      }
      int matches{0};
      for (const auto& number : my_numbers_vector) {
        for (const auto& winning_number : winning_numbers_vector) {
          if (number == winning_number) {
            ++matches;
          }
        }
      }
      points_line[game_number_int] = matches;
    }

    for (int i{1}; i <= 214; ++i) {
      ocurrencies_line[i] += 1;
    }

    for (int i{1}; i <= 214; ++i) {
      for (int k{1}; k <= ocurrencies_line[i]; ++k) {
        for (int j{i + 1}; j <= (points_line[i] + i); ++j) {
          ocurrencies_line[j] += 1;
        }
      }
    }

    for (const auto& a : ocurrencies_line) {
      total += a.second;
    }
    std::cout << total << std::endl;
}