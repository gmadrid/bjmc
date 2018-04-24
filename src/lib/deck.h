#ifndef DECK_H
#define DECK_H

#include <vector>
#include <iostream>

#include "card.h"

class Deck {
 public:
  Deck();
  void Shuffle() noexcept;

  Card Next() noexcept {
    auto next = cards_.back();
    cards_.pop_back();
    return next;
  }
  int Size() const noexcept { return cards_.size(); }

 private:
  std::vector<Card> cards_;
};

#endif  // DECK_H
