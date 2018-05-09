#include "../lib/chipstack.h"

#include "gtest/gtest.h"

namespace bjmc {
namespace tests {

TEST(Chipstack, Ctor) {
  EXPECT_EQ(50, Chipstack(50).Value());
  EXPECT_EQ(-50, Chipstack(-50).Value());
}

TEST(Chipstack, Xfer) {
  Chipstack from(50);
  Chipstack to(50);

  from.TransferFrom(20, &to);
  EXPECT_EQ(30, from.Value());
  EXPECT_EQ(70, to.Value());

  from.TransferFrom(-30, &to);
  EXPECT_EQ(60, from.Value());
  EXPECT_EQ(40, to.Value());
}
}  // namespace tests
}  // namespace bjmc
