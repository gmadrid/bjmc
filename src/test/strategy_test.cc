#include "../lib/strategy.h"

#include "gtest/gtest.h"

namespace bjmc {
namespace tests {

TEST(BasicDealerStrategy, Simple) {
  BasicDealerStrategy strategy;
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"3S", "2H"}));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"TS", "6H"}));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"3S", "2H", "TH"}));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"AS", "5H"}));
  EXPECT_EQ(Action::Hit, strategy.ChooseAction(Hand{"AS", "3H", "2C"}));

  EXPECT_EQ(Action::Stay, strategy.ChooseAction(Hand{"AS", "3H", "3C"}));
  EXPECT_EQ(Action::Stay, strategy.ChooseAction(Hand{"AS", "TH"}));
  EXPECT_EQ(Action::Stay,
            strategy.ChooseAction(Hand{"TS", "3H", "2C", "AC", "AD"}));
  EXPECT_EQ(Action::Stay, strategy.ChooseAction(Hand{"TS", "TH"}));
  EXPECT_EQ(Action::Stay, strategy.ChooseAction(Hand{"TS", "AH"}));
}

}  // namespace tests
}  // namespace bjmc
