#include "card.h"

#include <iostream>

constexpr const char pip_lookup[] = "A23456789TJQK";
constexpr const size_t num_pips = sizeof(pip_lookup) / sizeof(*pip_lookup);
constexpr const char suit_lookup[] = "SHCD";
constexpr const size_t num_suits = sizeof(suit_lookup) / sizeof(*suit_lookup);

using std::string;

Card::Card(const std::string &desc) noexcept {
  // assumes no spaces.
  auto pc = toupper(desc[0]);
  auto sc = toupper(desc[1]);
  auto pi = std::find(pip_lookup, pip_lookup + num_pips, pc);
  auto si = std::find(suit_lookup, suit_lookup + num_suits, sc);

  if (pi >= pip_lookup + sizeof(pip_lookup) ||
      si >= suit_lookup + sizeof(suit_lookup)) {
    suit_ = Suit::Invalid;
    pips_ = Pips::Invalid;
  } else {
    pips_ = static_cast<Pips>(pi - pip_lookup + 1);
    suit_ = static_cast<Suit>(si - suit_lookup + 1);
  }
}

string Card::ToString() const noexcept {
  if (suit_ == Suit::Invalid || pips_ == Pips::Invalid) {
    return "XX";
  }
  
  char buf[3];
  buf[0] = pip_lookup[static_cast<int>(pips_) - 1];
  buf[1] = suit_lookup[static_cast<int>(suit_) - 1];
  buf[2] = '\0';
  return buf;
}

