#include "strategy.h"

namespace bjmc {

Action BasicDealerStrategy::ChooseAction(const Hand &dealer_hand) const
    noexcept {
  return dealer_hand.Value() < 17 ? Action::Hit : Action::Stay;
}

} // namespace bjmc
