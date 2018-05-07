#ifndef CARD_H
#define CARD_H

#include <string>

#include "absl/strings/string_view.h"

namespace bjmc {

enum class Suit : short { Invalid = 0, Spades = 1, Hearts, Clubs, Diamonds };

enum class Pips : short {
  Invalid = 0,
  Ace = 1,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King
};

/**
 * A fundamental unit in a card deck.
 * Each Card has a value as well as a Pip and a Suit.
 * (Suits are irrelevant for Blackjack, but the user expects them in the UI.)
 */
class Card {
 public:
  Card() = delete;

  // TODO: swap suit, pips
  Card(Suit suit, Pips pips) noexcept : suit_(suit), pips_(pips) {}

  // TODO: eliminate invalid cards
  explicit Card(const absl::string_view &desc) noexcept;

  ~Card() = default;
  Card(const Card &card) = default;
  Card(Card &&card) = default;
  Card &operator=(const Card &other) = default;
  Card &operator=(Card &&other) = default;

  friend bool operator==(const Card &lhs, const Card &rhs) noexcept {
    return lhs.suit_ == rhs.suit_ && lhs.pips_ == rhs.pips_;
  }

  Suit Suit() const noexcept { return suit_; }
  Pips Pips() const noexcept { return pips_; }

  int Value() const noexcept {
    auto pip_value = static_cast<int>(pips_);
    return pip_value > 9 ? 10 : pip_value;
  }

  std::string ToString() const noexcept;

 private:
  enum Suit suit_;
  enum Pips pips_;
};

}  // namespace bjmc

#endif  // CARD_H
