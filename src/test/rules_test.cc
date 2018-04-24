#include "../lib/rules.h"

#include "gtest/gtest.h"

TEST(Rules, DealerHitsTest) {
  Rules rules;
  
  EXPECT_TRUE(rules.DealerHits(Hand{ "3S", "2S" }));
  EXPECT_TRUE(rules.DealerHits(Hand{ "TD", "6C" }));
  EXPECT_FALSE(rules.DealerHits(Hand{ "TH", "7S" }));
  EXPECT_FALSE(rules.DealerHits(Hand{ "TC", "AS" }));
  EXPECT_TRUE(rules.DealerHits(Hand{ "3S", "2S", "3C", "2H", "3D", "2D" }));
  EXPECT_TRUE(rules.DealerHits(Hand{ "AS", "5S" }));
  EXPECT_FALSE(rules.DealerHits(Hand{ "AD", "6C" }));
  EXPECT_FALSE(rules.DealerHits(Hand{ "AS", "JC" }));
}
