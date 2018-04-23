#ifndef CARD_H
#define CARD_H

#include <string>

enum class Suit : short {
  Invalid = 0, Spades = 1, Hearts, Clubs, Diamonds
};

enum class Pips : short {
  Invalid = 0,
  Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
  Jack, Queen, King
};

class Card {
public:
  Card() = delete;
  
  // TODO: swap suit, pips
  Card(Suit suit, Pips pips) noexcept : suit_(suit), pips_(pips) {}

  // TODO: eliminate invalid cards
  explicit Card(const std::string &desc) noexcept;

  ~Card() = default;
  Card(const Card& card) = default;
  Card(Card&& card) = default;
  Card& operator=(const Card& other) = default;
  Card& operator=(Card &&other) = default;

  Suit suit() const noexcept { return suit_; }
  Pips pips() const noexcept { return pips_; }

  std::string ToString() const noexcept;
  static Card FromString(const std::string &str) noexcept;

private:
  
  Suit suit_;
  Pips pips_;
};

#endif  // CARD_H
