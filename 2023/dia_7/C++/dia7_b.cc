// Autor: Darío Fajardo

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define HIGH_CARD 0
#define PAREJA 1
#define DOBLE_PAREJA 2
#define TRIO 3
#define FULL 4
#define POKER 5
#define CINCO 6

class Hand {
 public:
  Hand(std::string hand, int bid) {
    cards_ = hand;
    bid_ = bid;
    std::map<char, int> card_count{{'A', 0}, {'K', 0}, {'Q', 0}, {'J', 0}, {'T', 0}, {'9', 0}, {'8', 0}, {'7', 0}, {'6', 0}, {'5', 0}, {'4', 0}, {'3', 0}, {'2', 0}};
    std::map<char, int> values{{'A', 14}, {'K', 13}, {'Q', 12}, {'J', 1}, {'T', 10}, {'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2}};
    for (const auto& card : cards_) {
      card_values_.push_back(values[card]);
      card_count[card]++;
    }
    char biggest_key{'A'};
    for (const auto& card : card_count) {
      if (card.second > card_count[biggest_key] && card.first != 'J') {
        biggest_key = card.first;
      }
    }
    card_count[biggest_key] += card_count['J'];
    card_count['J'] = 0;
    combination_ = HIGH_CARD;
    for (const auto& card : card_count) {
      if (card.second == 4) {
        combination_ = POKER;
      } else if (card.second == 3) {
        if (combination_ == PAREJA) {
          combination_ = FULL;
        } else {
          combination_ = TRIO;
        }
      } else if (card.second == 2) {
        if (combination_ == PAREJA) {
          combination_ = DOBLE_PAREJA;
        } else if (combination_ == TRIO) {
          combination_ = FULL;
        } else {
          combination_ = PAREJA;
        }
      } else if (card.second == 5) {
        combination_ = CINCO;
      }
    }
  }
  int GetBid() const { return bid_;  }
  int GetCombination() const { return combination_; }
  std::string GetCards() const { return cards_; }
  std::vector<int> GetCardsValues() const { return card_values_; }
  bool operator<(const Hand& other) const {
    if (combination_ != other.GetCombination()) {
      return combination_ < other.GetCombination();
    } else {
      for (int i = 0; i < cards_.size(); i++) {
        if (cards_[i] != other.GetCards()[i]) {
          return card_values_[i] < other.GetCardsValues()[i];
        }
      }
    }
  }
 private:
  std::string cards_;
  std::vector<int> card_values_;
  int bid_;
  int combination_;
};

int main() {
  std::ifstream file{"input/input.txt", std::ios_base::in};
  std::string line;
  std::vector<Hand> ranking;
  while(getline(file, line)) {
    std::string hand{line.substr(0, line.find(' '))};
    int points{std::stoi(line.substr(line.find(' ') + 1, line.size() - 1))};
    Hand new_hand{hand, points};
    ranking.push_back(new_hand);
  }
  std::sort(ranking.begin(), ranking.end());
  int total_points{0};
  for (int i = 0; i < ranking.size(); i++) {
    std::cout << "Rank: " << i + 1 << " Hand: " << ranking[i].GetCards() << " Combination: " << ranking[i].GetCombination() << std::endl;
    total_points += ranking[i].GetBid() * (i + 1);
  }
  std::cout << total_points << std::endl;
  return 0;
}