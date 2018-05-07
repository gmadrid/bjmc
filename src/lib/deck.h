#ifndef DECK_H
#define DECK_H

#include <random>
#include <vector>

#include "card.h"

namespace bjmc {

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
  std::random_device rnd_;
};

}  // namespace bjmc

#endif  // DECK_H
