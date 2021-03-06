#ifndef HAND_H
#define HAND_H

#include "card.h"

#include <vector>

namespace bjmc {

class Hand {
 public:
  // Create a new empty hand.
  Hand() noexcept {}

  // Mostly for testing. Create a hand from a list of card names.
  Hand(std::initializer_list<std::string> lst) noexcept {
    for (const auto &p : lst) {
      cards_.emplace_back(p);
    }
  }

  ~Hand() = default;
  Hand(const Hand &hand) = default;
  Hand(Hand &&hand) = default;
  Hand &operator=(const Hand &other) = default;
  Hand &operator=(Hand &&other) = default;

  const Card &operator[](size_t index) const noexcept { return cards_[index]; }

  size_t Size() const noexcept { return cards_.size(); }

  void AddCard(Card card) noexcept;
  Hand Split() noexcept;

  int Value() const noexcept;
  bool IsSoft() const noexcept;
  bool IsBusted() const noexcept { return Value() > 21; }  // TEST

  std::string ToString() const noexcept;

 private:
  void InvalidateValues() const noexcept { values_valid_ = false; }
  void ComputeValues() const noexcept;

  std::vector<Card> cards_;

  mutable bool values_valid_ = false;
  mutable int total_ = 0;
  mutable bool is_soft_ = false;
};

}  // namespace bjmc

#endif  // HAND_H
