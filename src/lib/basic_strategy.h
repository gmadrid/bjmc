#ifndef BASIC_STRATEGY_H
#define BASIC_STRATEGY_H

#include "strategy.h"

class BasicStrategy : public PlayerStrategy {
 public:
  Action ChooseAction(const Hand &player_hand, Card dealer_card) const noexcept override;
};

#endif  // BASIC_STRATEGY_H
