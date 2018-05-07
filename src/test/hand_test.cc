#include "../lib/hand.h"

#include "gtest/gtest.h"

namespace bjmc {

TEST(Hand, Empty) {
  Hand hand;

  EXPECT_EQ(0, hand.Value());
  EXPECT_FALSE(hand.IsSoft());
}

TEST(Hand, Basic) {
  auto hand = Hand{"AH", "JS"};

  EXPECT_EQ(21, hand.Value());
  EXPECT_TRUE(hand.IsSoft());
}

TEST(Hand, AddingCards) {
  Hand hand;

  hand.AddCard(Card("3C"));
  EXPECT_EQ(3, hand.Value());
  EXPECT_FALSE(hand.IsSoft());

  hand.AddCard(Card("6D"));
  EXPECT_EQ(9, hand.Value());
  EXPECT_FALSE(hand.IsSoft());

  hand.AddCard(Card("AS"));
  EXPECT_EQ(20, hand.Value());
  EXPECT_TRUE(hand.IsSoft());

  hand.AddCard(Card("TC"));
  EXPECT_EQ(20, hand.Value());
  EXPECT_FALSE(hand.IsSoft());

  hand.AddCard(Card("AD"));
  EXPECT_EQ(21, hand.Value());
  EXPECT_FALSE(hand.IsSoft());

  hand.AddCard(Card("2C"));
  EXPECT_EQ(23, hand.Value());
  EXPECT_FALSE(hand.IsSoft());
}

TEST(Hand, FromInitList) {
  auto hand = Hand{"2S", "3H", "4H"};
  EXPECT_EQ(9, hand.Value());
  EXPECT_FALSE(hand.IsSoft());
}

TEST(Hand, CopyCtor) {
  auto hand = Hand{"AC", "2D", "3S", "4C"};
  auto c(hand);

  EXPECT_EQ(hand.Value(), c.Value());
  EXPECT_EQ(hand.IsSoft(), c.IsSoft());
}

TEST(Hand, CopyAssign) {
  auto hand = Hand{"2C", "4S", "9S"};
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
  auto hand = Hand{"2S", "8D"};
  EXPECT_EQ(10, hand.Value());
  EXPECT_FALSE(hand.IsSoft());

  hand = Hand{"2S", "8D", "9C"};
  EXPECT_EQ(19, hand.Value());
  EXPECT_FALSE(hand.IsSoft());
}

TEST(Hand, HandTotalWithAces) {
  auto hand = Hand{"AS", "9C", "9C"};
  EXPECT_EQ(19, hand.Value());
  EXPECT_FALSE(hand.IsSoft());
}

TEST(Hand, SoftWithAces) {
  auto hand = Hand{"AD", "TC"};
  EXPECT_EQ(21, hand.Value());
  EXPECT_TRUE(hand.IsSoft());

  hand = Hand{"AD", "AC", "AH"};
  EXPECT_EQ(13, hand.Value());
  EXPECT_TRUE(hand.IsSoft());
}

TEST(Hand, Indexing) {
  Hand hand{"AS", "2C", "3H", "4D"};
  EXPECT_EQ(Card{"AS"}, hand[0]);
  EXPECT_EQ(Card{"2C"}, hand[1]);
  EXPECT_EQ(Card{"3H"}, hand[2]);
  EXPECT_EQ(Card{"4D"}, hand[3]);

  hand[1] = Card("TD");
  EXPECT_EQ(Card{"AS"}, hand[0]);
  EXPECT_EQ(Card{"TD"}, hand[1]);
  EXPECT_EQ(Card{"3H"}, hand[2]);
  EXPECT_EQ(Card{"4D"}, hand[3]);
}

TEST(Hand, ConstIndexing) {
  const Hand hand{"AS", "2C", "3H", "4D"};
  EXPECT_EQ(Card{"AS"}, hand[0]);
  EXPECT_EQ(Card{"2C"}, hand[1]);
  EXPECT_EQ(Card{"3H"}, hand[2]);
  EXPECT_EQ(Card{"4D"}, hand[3]);
}

TEST(Hand, Size) {
  Hand hand;
  EXPECT_EQ(0, hand.Size());

  hand.AddCard(Card{"3S"});
  EXPECT_EQ(1, hand.Size());

  hand.AddCard(Card{"4D"});
  EXPECT_EQ(2, hand.Size());

  hand.AddCard(Card{"QH"});
  EXPECT_EQ(3, hand.Size());
}

}  // namespace bjmc
