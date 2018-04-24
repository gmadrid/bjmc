#include "basic_strategy.h"

#include "rules.h"

namespace bjmc {

// TODO: deal with double allowed after split
// Tables from
// https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
constexpr bool should_split[10][10]{
    /*               A      2      3      4      5      6      7      8      9
       T */
    /*   (A,A) */ {true, true, true, true, true, true, true, true, true, true},
    /* (2,2) */
    {false, false, false, true, true, true, true, false, false, false},
    /* (3,3) */
    {false, false, false, true, true, true, true, false, false, false},
    /* (4,4) */
    {false, false, false, false, false, false, false, false, false, false},
    /* (5,5) */
    {false, false, false, false, false, false, false, false, false, false},
    /* (6,6) */
    {false, false, true, true, true, true, false, false, false, false},
    /* (7,7) */
    {false, true, true, true, true, true, true, false, false, false},
    /* (8,8) */ {true, true, true, true, true, true, true, true, true, true},
    /* (9,9) */ {false, true, true, true, true, true, false, true, true, false},
    /* (T,T) */
    {false, false, false, false, false, false, false, false, false, false}};

constexpr Action soft_actions[8][10]{
    /*          A             2             3                4               5
     */
    /*  6               7             8             9             T */
    /*   2 */ {Action::Hit, Action::Hit, Action::Hit, Action::Hit,
               Action::Double, Action::Double, Action::Hit, Action::Hit,
               Action::Hit, Action::Hit},
    /* 3 */
    {Action::Hit, Action::Hit, Action::Hit, Action::Hit, Action::Double,
     Action::Double, Action::Hit, Action::Hit, Action::Hit, Action::Hit},
    /* 4 */
    {Action::Hit, Action::Hit, Action::Hit, Action::Double, Action::Double,
     Action::Double, Action::Hit, Action::Hit, Action::Hit, Action::Hit},
    /* 5 */
    {Action::Hit, Action::Hit, Action::Hit, Action::Double, Action::Double,
     Action::Double, Action::Hit, Action::Hit, Action::Hit, Action::Hit},
    /* 6 */
    {Action::Hit, Action::Hit, Action::Double, Action::Double, Action::Double,
     Action::Double, Action::Hit, Action::Hit, Action::Hit, Action::Hit},
    /* 7 */
    {Action::Hit, Action::Double, Action::Double, Action::Double,
     Action::Double, Action::Double, Action::Stay, Action::Stay, Action::Hit,
     Action::Hit},
    /* 8 */
    {Action::Stay, Action::Stay, Action::Stay, Action::Stay, Action::Stay,
     Action::Double, Action::Stay, Action::Stay, Action::Stay, Action::Stay},
    /* 9 */
    {Action::Stay, Action::Stay, Action::Stay, Action::Stay, Action::Stay,
     Action::Stay, Action::Stay, Action::Stay, Action::Stay, Action::Stay}};

constexpr Action hard_actions[8][10]{
    /*           A               2               3               4 5 */
    /*  6               7               8               9               T */
    /*    9 */ {Action::Hit, Action::Hit, Action::Double, Action::Double,
                Action::Double, Action::Double, Action::Hit, Action::Hit,
                Action::Hit, Action::Hit},
    /* 10 */
    {Action::Hit, Action::Double, Action::Double, Action::Double,
     Action::Double, Action::Double, Action::Double, Action::Double,
     Action::Double, Action::Hit},
    /* 11 */
    {Action::Double, Action::Double, Action::Double, Action::Double,
     Action::Double, Action::Double, Action::Double, Action::Double,
     Action::Double, Action::Double},
    /* 12 */
    {Action::Hit, Action::Hit, Action::Hit, Action::Stay, Action::Stay,
     Action::Stay, Action::Hit, Action::Hit, Action::Hit, Action::Hit},
    /* 13 */
    {Action::Hit, Action::Stay, Action::Stay, Action::Stay, Action::Stay,
     Action::Stay, Action::Hit, Action::Hit, Action::Hit, Action::Hit},
    /* 14 */
    {Action::Hit, Action::Stay, Action::Stay, Action::Stay, Action::Stay,
     Action::Stay, Action::Hit, Action::Hit, Action::Hit, Action::Hit},
    /* 15 */
    {Action::Hit, Action::Stay, Action::Stay, Action::Stay, Action::Stay,
     Action::Stay, Action::Hit, Action::Hit, Action::Hit, Action::Hit},
    /* 16 */
    {Action::Hit, Action::Stay, Action::Stay, Action::Stay, Action::Stay,
     Action::Stay, Action::Hit, Action::Hit, Action::Hit, Action::Hit}};

bool ShouldSplit(const Hand &player_hand, Card dealer_card) {
  // Assumes both cards are the same value.
  return should_split[static_cast<int>(player_hand[0].Pips()) - 1]
                     [static_cast<int>(dealer_card.Pips()) - 1];
}

Action SoftTwoAction(const Hand &player_hand, Card dealer_card) {
  // Assumes one (and only one) card is an Ace.
  Card non_ace =
      player_hand[0].Pips() == Pips::Ace ? player_hand[1] : player_hand[0];

  return soft_actions[static_cast<int>(non_ace.Pips()) - 2]
                     [static_cast<int>(dealer_card.Pips()) - 1];
}

Action BasicStrategy::ChooseAction(const Hand &player_hand,
                                   Card dealer_card) const noexcept {
  Rules rules;
  if (rules.PlayerCanSplit(player_hand) &&
      ShouldSplit(player_hand, dealer_card)) {
    return Action::Split;
  }

  if (player_hand.Size() == 2 && (player_hand[0].Pips() == Pips::Ace ||
                                  player_hand[1].Pips() == Pips::Ace)) {
    return SoftTwoAction(player_hand, dealer_card);
  }

  int value = player_hand.Value();
  if (value < 9)
    return Action::Hit;
  if (value > 16)
    return Action::Stay;

  Action action =
      hard_actions[value - 9][static_cast<int>(dealer_card.Pips()) - 1];
  if (action == Action::Double) {
    if (player_hand.Size() == 2) {
      return Action::Double;
    } else {
      return Action::Hit;
    }
  }

  return action;
}

} // namespace bjmc
