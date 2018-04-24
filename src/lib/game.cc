#include "game.h"

#include <iostream>

namespace bjmc {

Game::Game(std::unique_ptr<DealerStrategy> dealer, std::unique_ptr<PlayerStrategy> player,
	   std::unique_ptr<Deck> deck)
  : dealer_(std::move(dealer)), player_(std::move(player)), deck_(std::move(deck)) {
}

void Game::simulate() {
  // TODO: better handling/sharing of the RNG.
  // TODO: allow reusing games, reshuffling deck.

  // The deck is assumed to be shuffled.
  DealStartingHands();
  RunPlayer();
  if (!player_hand_.IsBusted()) {
    RunDealer();
  }

  FindWinner();
}

void Game::DealStartingHands() {
  player_hand_.AddCard(deck_->Next());
  dealer_hand_.AddCard(deck_->Next());
  player_hand_.AddCard(deck_->Next());
  dealer_hand_.AddCard(deck_->Next());

  std::cout << "Player: " << player_hand_.ToString() << std::endl;
  std::cout << "Dealer: " << dealer_hand_.ToString() << std::endl;
}

Card Game::DealerCard() const noexcept {
  return dealer_hand_[0];
}

void Game::RunPlayer() {
  while(!player_hand_.IsBusted()) {
    auto action = player_->ChooseAction(player_hand_, DealerCard());
    if (action == Action::Stay) return;

    player_hand_.AddCard(deck_->Next());
    std::cout << "Player: " << player_hand_.ToString() << std::endl;
  }
}

void Game::RunDealer() {
  while(!dealer_hand_.IsBusted()) {
    auto action = dealer_->ChooseAction(dealer_hand_);
    if (action == Action::Stay) return;

    dealer_hand_.AddCard(deck_->Next());
    std::cout << "Dealer: " << dealer_hand_.ToString() << std::endl;
  }
}

void Game::FindWinner() {
}

}  // namespace bjmc
