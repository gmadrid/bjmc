#include "../lib/hand.h"

#include "gtest/gtest.h"

TEST(Hand, Basic) {
  auto hand = Hand(Card("AH"), Card("JS"));

  EXPECT_EQ(21, hand.Value());
  EXPECT_TRUE(hand.IsSoft());
}

TEST(Hand, FromInitList) {
  auto hand = Hand{ "2S", "3H", "4H"};
  EXPECT_EQ(9, hand.Value());
  EXPECT_FALSE(hand.IsSoft());
}

TEST(Hand, CopyCtor) {
  auto hand = Hand{ "AC", "2D", "3S", "4C"};
  auto c(hand);

  EXPECT_EQ(hand.Value(), c.Value());
  EXPECT_EQ(hand.IsSoft(), c.IsSoft());
}

TEST(Hand, CopyAssign) {
  auto hand = Hand{ "2C", "4S", "9S" };
  auto c = Hand{"3S", "8H"};
  c = hand;

  EXPECT_EQ(hand.Value(), c.Value());
  EXPECT_EQ(hand.IsSoft(), c.IsSoft());
}

TEST(Hand, MoveCtor) {
  auto hand = Hand{"8C", "AC", "AD", "7H"};
  auto c(std::move(hand));

  EXPECT_EQ(17, c.Value());
  EXPECT_FALSE(c.IsSoft());

  auto hand2 = Hand{"AH", "JC"};
  auto c2(std::move(hand2));
  EXPECT_EQ(21, c2.Value());
  EXPECT_TRUE(c2.IsSoft());
}

TEST(Hand, MoveAssign) {
  auto hand = Hand{"3C", "2H"};
  auto c = Hand{"8H", "7H"};

  c = std::move(hand);
  EXPECT_EQ(5, c.Value());
  EXPECT_FALSE(c.IsSoft());

  auto hand2 = Hand{"2C", "2H"};
  auto c2 = Hand{"AH", "JC"};
  c2 = std::move(hand2);
  EXPECT_EQ(4, c2.Value());
  EXPECT_FALSE(c2.IsSoft());

  auto hand3 = Hand{"AH", "QS"};
  auto c3 = Hand{"2c", "2S"};
  c3 = std::move(hand3);
  EXPECT_EQ(21, c3.Value());
  EXPECT_TRUE(c3.IsSoft());
}

TEST(Hand, HardTotalNoAces) {
  auto hand = Hand{ "2S", "8D"};
  EXPECT_EQ(10, hand.Value());
  EXPECT_FALSE(hand.IsSoft());

  hand = Hand{ "2S", "8D", "9C"};
  EXPECT_EQ(19, hand.Value());
  EXPECT_FALSE(hand.IsSoft());
}

TEST(Hand, HandTotalWithAces) {
  auto hand = Hand{ "AS", "9C", "9C"};
  EXPECT_EQ(19, hand.Value());
  EXPECT_FALSE(hand.IsSoft());
}

TEST(Hand, SoftWithAces) {
  auto hand = Hand{ "AD", "TC" };
  EXPECT_EQ(21, hand.Value());
  EXPECT_TRUE(hand.IsSoft());

  hand = Hand{"AD", "AC", "AH"};
  EXPECT_EQ(13, hand.Value());
  EXPECT_TRUE(hand.IsSoft());
}
