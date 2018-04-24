#include "deck.h"

#include <algorithm>

namespace bjmc {

Deck::Deck() {
  cards_.reserve(52);

  for (int suit = static_cast<int>(Suit::Spades);
       suit <= static_cast<int>(Suit::Diamonds);
       ++suit) {
    for (int pips = static_cast<int>(Pips::Ace);
	 pips <= static_cast<int>(Pips::King);
	 ++pips) {
      cards_.emplace_back(static_cast<Suit>(suit),
			  static_cast<Pips>(pips));
    }
  }
}

void Deck::Shuffle() noexcept {
  std::shuffle(cards_.begin(), cards_.end(), rnd_);
}

}  // namespace bjmc
