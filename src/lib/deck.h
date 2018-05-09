#ifndef DECK_H
#define DECK_H

#include <random>
#include <vector>

#include "card.h"

namespace bjmc {

class Deck {
 public:
  Deck();
  Deck(std::initializer_list<std::string> lst) noexcept {
    cards_.reserve(lst.size());
    for (const auto &p : lst) {
      cards_.emplace_back(p);
    }

    // When dealing, cards are popped off the end.
    // This ctor is mostly used for testing, and it's easier to think about when
    // the cards are dealt in the order they are seen in the init list.
    std::reverse(cards_.begin(), cards_.end());
  }
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
