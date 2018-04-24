#include "../lib/deck.h"

#include "gtest/gtest.h"

namespace bjmc {

TEST(Deck, Basic) {
  Deck deck;

  EXPECT_EQ(52, deck.Size());

  EXPECT_EQ(Card("KD"), deck.Next());
  EXPECT_EQ(51, deck.Size());

  EXPECT_EQ(Card("QD"), deck.Next());
  EXPECT_EQ(50, deck.Size());
}

} // namespace bjmc
