#include "../lib/wager.h"

#include "gtest/gtest.h"

#include "../lib/chipstack.h"
#include "../lib/deck.h"

namespace bjmc {
namespace tests {

constexpr int wager_size = 100;
constexpr int starting_stack_size = 1000;

class WagerTest : public ::testing::Test {
 public:
  WagerTest() : stack_(starting_stack_size), wager_(wager_size, &stack_) {}

 protected:
  Chipstack stack_;
  Wager wager_;
};

TEST_F(WagerTest, Ctor) {
  EXPECT_EQ(0, wager_.Hand()->Size());
  EXPECT_EQ(wager_size, wager_.Stack()->Value());
  EXPECT_EQ(starting_stack_size - wager_size, stack_.Value());
}

TEST_F(WagerTest, StartingHand) {
  Deck deck{"AH", "JC"};
  auto start_wager_size = wager_.Stack()->Value();
  auto start_stack_size = stack_.Value();

  wager_.DealStartingHand(&deck);

  EXPECT_EQ(0, deck.Size());

  EXPECT_EQ(2, wager_.Hand()->Size());
  EXPECT_EQ(Card("AH"), (*wager_.Hand())[0]);
  EXPECT_EQ(Card("JC"), (*wager_.Hand())[1]);

  EXPECT_EQ(start_wager_size, wager_.Stack()->Value());
  EXPECT_EQ(start_stack_size, stack_.Value());
}

TEST_F(WagerTest, Hit) {
  Deck deck{"2C", "3H", "4H", "6H"};
  wager_.DealStartingHand(&deck);

  wager_.Hit(&deck);
  EXPECT_EQ(Card("4H"), (*wager_.Hand())[2]);
  EXPECT_EQ(9, wager_.Hand()->Value());
}

TEST_F(WagerTest, DoubleDown) {
  Deck deck{"6H", "5H", "TH", "7H"};
  wager_.DealStartingHand(&deck);

  wager_.DoubleDown(&deck, &stack_);
  EXPECT_EQ(21, wager_.Hand()->Value());

  EXPECT_EQ(1, deck.Size());
  EXPECT_EQ(800, stack_.Value());
  EXPECT_EQ(200, wager_.Stack()->Value());
  EXPECT_EQ(21, wager_.Hand()->Value());
}

TEST_F(WagerTest, Split) {
  Deck deck{"AH", "AD", "TH", "9D"};
  wager_.DealStartingHand(&deck);

  auto wager2 = wager_.Split(&deck, &stack_);
  EXPECT_EQ(21, wager_.Hand()->Value());
  EXPECT_EQ(20, wager2.Hand()->Value());
  EXPECT_EQ(wager_size, wager_.Stack()->Value());
  EXPECT_EQ(wager_size, wager2.Stack()->Value());

  EXPECT_EQ(starting_stack_size - 2 * wager_size, stack_.Value());
}

}  // namespace tests
}  // namespace bjmc
