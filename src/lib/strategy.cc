#include "strategy.h"

Action BasicDealerStrategy::ChooseAction(const Hand &dealer_hand) const
    noexcept {
  return dealer_hand.Value() < 17 ? Action::Hit : Action::Stay;
}
