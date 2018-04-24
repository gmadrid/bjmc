#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "hand.h"

class Player {
  Player();

  ~Player() = default;
  Player(const Player &player) = default;
  Player(Player &&player) = default;
  Player &operator=(const Player &other) = default;
  Player &operator=(Player &&other) = default;

  // TODO: test this stuff
  std::string Name() { return name_; }
  void SetName(std::string_view name) { name_ = name; }

  void DealCard(Card card) { hand_.AddCard(card); }
  int Total() const { return hand_.Value(); }
  bool IsBusted() const { return Total() > 21; }

  const Hand &Hand() { return hand_; }

private:
  Hand hand_;
  std::string name_;
};

#endif // PLAYER_H
