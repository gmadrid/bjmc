#ifndef SEAT_H
#define SEAT_H

#include <memory>

#include "deck.h"
#include "player.h"
#include "wager.h"

namespace bjmc {

class Seat {
 public:
  Seat(std::unique_ptr<Player> player) : player_(std::move(player)) {}

  Seat() = delete;
  ~Seat() = default;
  Seat(const Seat &) = default;
  Seat(Seat &&) = default;
  Seat &operator=(const Seat &) = default;
  Seat &operator=(Seat &&) = default;

  void MakeWager() noexcept;
  void DealHand(Deck *) noexcept;

 private:
  std::unique_ptr<Player> player_;
  std::vector<Wager> wagers_;
};

}  // namespace bjmc

#endif  // SEAT_H
