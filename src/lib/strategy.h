#ifndef STRATEGY_H
#define STRATEGY_H

#include "hand.h"

namespace bjmc {

enum class Action {
  Stay,
  Hit,
  Insurance,
  Split,
  Double  // DoubleDown
};

// The dealer has only one decision.
class DealerStrategy {
 public:
  virtual Action ChooseAction(const Hand &dealer_hand) const noexcept = 0;
};

class PlayerStrategy {
 public:
  virtual Action ChooseAction(const Hand &player_hand, Card dealer_card) const
      noexcept = 0;
};

class BasicDealerStrategy : public DealerStrategy {
 public:
  Action ChooseAction(const Hand &dealer_hand) const noexcept override;
};

}  // namespace bjmc

#endif  // STRATEGY_H
