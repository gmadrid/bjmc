#ifndef GAME_H
#define GAME_H

#include <memory>

#include "deck.h"
#include "strategy.h"

namespace bjmc {

class Game {
  // 1. Make a Dealer player with dealer strategy.
  // 2. Make a Player with basic strategy.
  // 3. Run the Player.
  // 4. Run the Dealer.
  // 5. Find winner.

 public:
  Game(std::unique_ptr<DealerStrategy> dealer,
       std::unique_ptr<PlayerStrategy> player,
       std::unique_ptr<Deck> shuffled_deck);

  void simulate();

  Game() = delete;
  Game(const Game &) = delete;
  Game(Game &&) = delete;
  Game &operator=(const Game &) = delete;
  Game &operator=(Game &&) = delete;

  Card DealerCard() const noexcept;

 private:
  void DealStartingHands();
  void RunPlayer();
  void RunDealer();
  void FindWinner();

  std::unique_ptr<DealerStrategy> dealer_;
  Hand dealer_hand_;

  std::unique_ptr<PlayerStrategy> player_;
  Hand player_hand_;

  std::unique_ptr<Deck> deck_;
};

}  // namespace bjmc

#endif  // GAME_H
