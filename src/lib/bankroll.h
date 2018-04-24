#ifndef BANKROLL_H
#define BANKROLL_H

namespace bjmc {

class Bankroll {
public:
  Bankroll(int starting_amount) : amount_(starting_amount){};

  Bankroll() = delete;
  ~Bankroll() = default;
  Bankroll(const Bankroll &) = default;
  Bankroll(Bankroll &&) = default;
  Bankroll &operator=(const Bankroll &) = default;
  Bankroll &operator=(Bankroll &&) = default;
}

private : int amount_;

} // namespace bjmc

#endif // BANKROLL_H
