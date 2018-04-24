#include "../lib/basic_strategy.h"

#include "gtest/gtest.h"

namespace bjmc {

TEST(BasicStrategy, Splits) {
  BasicStrategy strategy;

  EXPECT_EQ(Action::Split, strategy.ChooseAction(Hand{"AS", "AH"}, Card("2H")));

  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"2D", "2C"}, Card("AH")));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"2D", "2C"}, Card("2H")));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"2D", "2C"}, Card("3H")));
  EXPECT_EQ(Action::Split, strategy.ChooseAction(Hand{"2D", "2C"}, Card("4H")));
  EXPECT_EQ(Action::Split, strategy.ChooseAction(Hand{"2D", "2C"}, Card("7H")));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"2D", "2C"}, Card("8H")));

  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"6D", "6C"}, Card("AH")));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"6D", "6C"}, Card("2H")));
  EXPECT_EQ(Action::Split, strategy.ChooseAction(Hand{"6D", "6C"}, Card("3H")));

  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"7D", "7C"}, Card("AH")));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"7D", "7C"}, Card("8H")));
  EXPECT_EQ(Action::Split, strategy.ChooseAction(Hand{"7D", "7C"}, Card("2H")));
  EXPECT_EQ(Action::Split, strategy.ChooseAction(Hand{"7D", "7C"}, Card("7H")));
}

TEST(BasicStrategy, TwoCardSoft) {
  BasicStrategy strategy;

  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"AS", "2C"}, Card("2C")));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"AS", "2C"}, Card("4C")));
  EXPECT_EQ(Action::Double,
            strategy.ChooseAction(Hand{"AS", "2C"}, Card("5C")));
  EXPECT_EQ(Action::Double,
            strategy.ChooseAction(Hand{"AS", "2C"}, Card("6C")));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"AS", "2C"}, Card("7C")));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"AS", "2C"}, Card("TC")));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"AS", "2C"}, Card("AC")));

  EXPECT_EQ(Action::Stay, strategy.ChooseAction(Hand{"8S", "AC"}, Card("2C")));
  EXPECT_EQ(Action::Stay, strategy.ChooseAction(Hand{"8S", "AC"}, Card("5C")));
  EXPECT_EQ(Action::Double,
            strategy.ChooseAction(Hand{"8S", "AC"}, Card("6C")));
  EXPECT_EQ(Action::Stay, strategy.ChooseAction(Hand{"8S", "AC"}, Card("7C")));
  EXPECT_EQ(Action::Stay, strategy.ChooseAction(Hand{"8S", "AC"}, Card("TC")));
  EXPECT_EQ(Action::Stay, strategy.ChooseAction(Hand{"8S", "AC"}, Card("AC")));
}

TEST(BasicStrategy, Doubles) {
  BasicStrategy strategy;

  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"3C", "7D"}, Card("AC")));
  EXPECT_EQ(Action::Double,
            strategy.ChooseAction(Hand{"3C", "7D"}, Card("2C")));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"3C", "7D"}, Card("TC")));

  EXPECT_EQ(Action::Hit,
            strategy.ChooseAction(Hand{"6C", "3D", "2H"}, Card("6C")));
}

TEST(BasicStrategy, Typical) {
  BasicStrategy strategy;

  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"5C", "7D"}, Card("AC")));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"5C", "7D"}, Card("2C")));
  EXPECT_EQ(Action::Stay, strategy.ChooseAction(Hand{"5C", "7D"}, Card("4C")));
  EXPECT_EQ(Action::Stay, strategy.ChooseAction(Hand{"5C", "7D"}, Card("6C")));
}

} // namespace bjmc
