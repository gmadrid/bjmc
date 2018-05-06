#include "table.h"

namespace bjmc {

  void Table::Simulate() noexcept {

    for (auto *seat : seats_) {
      seat.MakeWager();
      seat.DealHand(&deck);
    }

    dealer_hand_.AddCard(deck.Next());
    dealer_hand_.AddCard(deck.Next());

    Card up_card = DealerCard();
    for (const auto &seat : seats_) {
      seat->Simulate(up_card);
    }

    // Check for actives and run dealer strat.
  }

}  // namespace bjmc
