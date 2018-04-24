#include "../lib/basic_strategy.h"
#include "../lib/card.h"
#include "../lib/deck.h"
#include "../lib/game.h"
#include "../lib/strategy.h"

int main() {
  auto dealer = std::make_unique<BasicDealerStrategy>();
  auto player = std::make_unique<BasicStrategy>();
  auto deck = std::make_unique<Deck>();
  deck->Shuffle();
  
  Game game(std::move(dealer), std::move(player), std::move(deck));
  game.simulate();
}
