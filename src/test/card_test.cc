#include "../lib/card.h"

#include "gtest/gtest.h"

TEST(Suits, AllSuits) {
  auto e1 = Suit::Spades;
  EXPECT_EQ(e1, Suit::Spades);
  e1 = Suit::Clubs;
  EXPECT_EQ(e1, Suit::Clubs);
  e1 = Suit::Hearts;
  EXPECT_EQ(e1, Suit::Hearts);
  e1 = Suit::Diamonds;
  EXPECT_EQ(e1, Suit::Diamonds);
}

TEST(Pips, AllPips) {
  auto pip = Pips::Ace;
  EXPECT_EQ(pip, Pips::Ace);
  pip = Pips::Two;
  EXPECT_EQ(pip, Pips::Two);
  pip = Pips::Three;
  EXPECT_EQ(pip, Pips::Three);
  pip = Pips::Four;
  EXPECT_EQ(pip, Pips::Four);
  pip = Pips::Five;
  EXPECT_EQ(pip, Pips::Five);
  pip = Pips::Six;
  EXPECT_EQ(pip, Pips::Six);
  pip = Pips::Seven;
  EXPECT_EQ(pip, Pips::Seven);
  pip = Pips::Eight;
  EXPECT_EQ(pip, Pips::Eight);
  pip = Pips::Nine;
  EXPECT_EQ(pip, Pips::Nine);
  pip = Pips::Ten;
  EXPECT_EQ(pip, Pips::Ten);
  pip = Pips::Jack;
  EXPECT_EQ(pip, Pips::Jack);
  pip = Pips::Queen;
  EXPECT_EQ(pip, Pips::Queen);
  pip = Pips::King;
  EXPECT_EQ(pip, Pips::King);
}

TEST(Card, Ctor) {
  Card card(Suit::Hearts, Pips::Queen);

  EXPECT_EQ(card.Suit(), Suit::Hearts);
  EXPECT_EQ(card.Pips(), Pips::Queen);
}

TEST(Card, CopyCtor) {
  Card src(Suit::Hearts, Pips::Queen);
  Card card(src);

  EXPECT_EQ(card.Suit(), Suit::Hearts);
  EXPECT_EQ(card.Pips(), Pips::Queen);
}

TEST(Card, CopyAssign) {
  Card src(Suit::Hearts, Pips::Queen);
  Card card(Suit::Diamonds, Pips::King);

  EXPECT_EQ(card.Suit(), Suit::Diamonds);
  EXPECT_EQ(card.Pips(), Pips::King);

  card = src;
  EXPECT_EQ(card.Suit(), Suit::Hearts);
  EXPECT_EQ(card.Pips(), Pips::Queen);
}

TEST(Card, MoveCtor) {
  Card src(Suit::Hearts, Pips::Queen);
  Card card(std::move(src));

  EXPECT_EQ(card.Suit(), Suit::Hearts);
  EXPECT_EQ(card.Pips(), Pips::Queen);
}

TEST(Card, MoveAssign) {
  Card src(Suit::Hearts, Pips::Queen);
  Card card(Suit::Diamonds, Pips::King);

  EXPECT_EQ(card.Suit(), Suit::Diamonds);
  EXPECT_EQ(card.Pips(), Pips::King);

  card = std::move(src);
  EXPECT_EQ(card.Suit(), Suit::Hearts);
  EXPECT_EQ(card.Pips(), Pips::Queen);
}

TEST(Card, ToString) {
  EXPECT_EQ("AH", Card(Suit::Hearts, Pips::Ace).ToString());
  EXPECT_EQ("TH", Card(Suit::Hearts, Pips::Ten).ToString());
  EXPECT_EQ("2S", Card(Suit::Spades, Pips::Two).ToString());
  EXPECT_EQ("JD", Card(Suit::Diamonds, Pips::Jack).ToString());
  EXPECT_EQ("QC", Card(Suit::Clubs, Pips::Queen).ToString());
  EXPECT_EQ("KC", Card(Suit::Clubs, Pips::King).ToString());
  EXPECT_EQ("7H", Card(Suit::Hearts, Pips::Seven).ToString());
  EXPECT_EQ("3D", Card(Suit::Diamonds, Pips::Three).ToString());
}

TEST(Card, FromString) {
  EXPECT_EQ("3S", Card("3S").ToString());
  EXPECT_EQ("AD", Card("AD").ToString());
  EXPECT_EQ("KH", Card("KH").ToString());
  EXPECT_EQ("8C", Card("8C").ToString());

  EXPECT_EQ("AS", Card("as").ToString());
  EXPECT_EQ("TH", Card("th").ToString());
  EXPECT_EQ("JC", Card("jc").ToString());
  EXPECT_EQ("QD", Card("qd").ToString());
  EXPECT_EQ("KS", Card("kS").ToString());
  EXPECT_EQ("8D", Card("8d").ToString());
}

TEST(Card, Values) {
  EXPECT_EQ(1, Card("AS").Value());
  EXPECT_EQ(2, Card("2S").Value());
  EXPECT_EQ(3, Card("3S").Value());
  EXPECT_EQ(4, Card("4S").Value());
  EXPECT_EQ(5, Card("5S").Value());
  EXPECT_EQ(6, Card("6S").Value());
  EXPECT_EQ(7, Card("7S").Value());
  EXPECT_EQ(8, Card("8S").Value());
  EXPECT_EQ(9, Card("9S").Value());
  EXPECT_EQ(10, Card("TS").Value());
  EXPECT_EQ(10, Card("JS").Value());
  EXPECT_EQ(10, Card("QS").Value());
  EXPECT_EQ(10, Card("KS").Value());
}

TEST(Card, Equality) {
  Card c1("AS");
  Card c2("AS");
  Card d1("AD");
  Card e1("TS");
  Card f1("5C");

  EXPECT_TRUE(c1 == c1);
  EXPECT_TRUE(c1 == c2);
  EXPECT_TRUE(c2 == c1);
  EXPECT_FALSE(c1 == d1);
  EXPECT_FALSE(c1 == e1);
  EXPECT_FALSE(c1 == f1);
}
