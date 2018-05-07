#ifndef BASIC_STRATEGY_H
#define BASIC_STRATEGY_H

#include "strategy.h"

namespace bjmc {

class BasicStrategy : public PlayerStrategy {
 public:
  Action ChooseAction(const Hand &player_hand, Card dealer_card) const
      noexcept override;
};

}  // namespace bjmc

#endif  // BASIC_STRATEGY_H
