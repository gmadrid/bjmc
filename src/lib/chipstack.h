#ifndef CHIPSTACK_H
#define CHIPSTACK_H

namespace bjmc {

class Chipstack {
 public:
  Chipstack(int starting_amount = 0) : amount_(starting_amount){};

  ~Chipstack() = default;
  Chipstack(const Chipstack &) = default;
  Chipstack(Chipstack &&) = default;
  Chipstack &operator=(const Chipstack &) = default;
  Chipstack &operator=(Chipstack &&) = default;

  void TransferFrom(int xfer, Chipstack *other) noexcept {
    amount_ -= xfer;
    other->amount_ += xfer;
  }

  int Value() const noexcept { return amount_; }

 private:
  int amount_;
};

}  // namespace bjmc

#endif  // CHIPSTACK_H
