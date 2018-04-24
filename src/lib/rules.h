#ifndef RULES_H
#define RULES_H

#include "hand.h"

class Rules {
 public:
  bool DealerHits(const Hand& hand) const noexcept {
    return hand.Value() < 17;
  }
  
  bool DealerWins(const Hand& dealer, const Hand& player) const noexcept {
    return dealer.Value() >= player.Value();
  }

  bool PlayerCanHit(const Hand& hand) const noexcept {
    return !hand.IsBusted();
  }
  
  bool PlayerCanSplit(const Hand& hand) const noexcept {
    return hand.Size() == 2 &&
      hand[0].Value() == hand[1].Value();
  }
  
  bool PlayerCanDoubleDown(const Hand& hand) const noexcept {
    return hand.Size() == 2;
  }
};

#endif  // RULES_H
