#ifndef WAGER_H
#define WAGER_H

#include "chipstack.h"
#include "hand.h"

namespace bjmc {

class Deck;

class Wager {
 public:
  Wager(int starting_wager, Chipstack *from_stack) {
    from_stack->TransferFrom(starting_wager, &stack_);
  };

  ~Wager() = default;
  Wager(const Wager &wager) = default;
  Wager(Wager &&wager) = default;
  Wager &operator=(const Wager &other) = default;
  Wager &operator=(Wager &&other) = default;

  void DealStartingHand(Deck *deck);
  void Hit(Deck *deck);
  void DoubleDown(Deck *deck, Chipstack *from_stack);
  Wager Split(Deck *deck, Chipstack *from_stack);

  Hand *Hand() { return &hand_; }
  Chipstack *Stack() { return &stack_; }

 private:
  bjmc::Hand hand_;
  Chipstack stack_;
};

}  // namespace bjmc

#endif  // WAGER_H
