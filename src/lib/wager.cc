#include "wager.h"

#include "deck.h"

namespace bjmc {

void Wager::DealStartingHand(Deck *deck) {
  hand_.AddCard(deck->Next());
  hand_.AddCard(deck->Next());
}

void Wager::Hit(Deck *deck) { hand_.AddCard(deck->Next()); }

void Wager::DoubleDown(Deck *deck, Chipstack *from_stack) {
  from_stack->TransferFrom(stack_.Value(), &stack_);
  hand_.AddCard(deck->Next());
}

Wager Wager::Split(Deck *deck, Chipstack *from_stack) {
  Wager other(stack_.Value(), from_stack);
  other.hand_ = hand_.Split();

  hand_.AddCard(deck->Next());
  other.hand_.AddCard(deck->Next());

  return other;
}
}  // namespace bjmc
