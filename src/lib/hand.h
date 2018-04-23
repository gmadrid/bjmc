#ifndef HAND_H
#define HAND_H

#include "card.h"

#include <vector>

class Hand {
 public:
  Hand(Card card1, Card card2) {
    cards_.emplace_back(std::move(card1));
    cards_.emplace_back(std::move(card2));
  }
  Hand(std::initializer_list<std::string> lst) {
    for (const auto &p : lst) {
      cards_.emplace_back(p);
    }
  }

  Hand() = delete;
  ~Hand() = default;
  Hand(const Hand& hand) = default;
  Hand(Hand&& hand) = default;
  Hand& operator=(const Hand& other) = default;
  Hand& operator=(Hand&& other) = default;

  int Value() const noexcept;
  bool IsSoft() const noexcept;

 private:
  void ComputeValues() const noexcept;
  
  std::vector<Card> cards_;

  mutable bool values_valid_ = false;
  mutable int total_ = 0;
  mutable bool is_soft_ = false;
};

#endif  // HAND_H
