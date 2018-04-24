#include "table.h"

namespace bjmc {

  void Table::Simulate() {

    // 1. Each Player makes a wager.
    // 2. Dealer deals a hand to all players and self.
    // 3. Foreach Player
    //    a. foreach Wager
    //       i. Run the Player's strategy
    //      ii. If Double Down
    //          - double wager
    //          - hit once and stop.
    //     iii. If Split
    //          - make a new Wager
    //          - Make a new Hand with each card, and replace Hands in Wagers.
    //          - hit each new Hand.
  }

}  // namespace bjmc
