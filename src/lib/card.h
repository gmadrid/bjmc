#ifndef CARD_H
#define CARD_H

#include <string>

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

class Card {
public:
  Card() = delete;

  // TODO: swap suit, pips
  Card(Suit suit, Pips pips) noexcept : suit_(suit), pips_(pips) {}

  // TODO: eliminate invalid cards
  explicit Card(const std::string_view &desc) noexcept;

  ~Card() = default;
  Card(const Card &card) = default;
  Card(Card &&card) = default;
  Card &operator=(const Card &other) = default;
  Card &operator=(Card &&other) = default;

  friend bool operator==(const Card &lhs, const Card &rhs) {
    return lhs.suit_ == rhs.suit_ && lhs.pips_ == rhs.pips_;
  }

  Suit Suit() const noexcept { return suit_; }
  Pips Pips() const noexcept { return pips_; }

  int Value() const noexcept {
    auto pip_value = static_cast<int>(pips_);
    return pip_value > 9 ? 10 : pip_value;
  }

  std::string ToString() const noexcept;
  static Card FromString(const std::string_view &str) noexcept;

private:
  ::bjmc::Suit suit_;
  ::bjmc::Pips pips_;
};

} // namespace bjmc

#endif // CARD_H
