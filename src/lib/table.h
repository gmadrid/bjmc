#ifndef TABLE_H
#define TABLE_H

#include "seat.h"
#include "strategy.h"

namespace bjmc {

class Table {
 public:
 Table(std::unique_ptr<DealerStrategy> dealer_strategy)
   : dealer_strategy_(std::move(dealer_strategy)) {}

  Table() = delete;
  ~Table() = default;
  Table(const Table &) = delete;
  Table(Table&&) = delete;
  Table& operator=(const Table &) = delete;
  Table& operator=(Table&&) = delete;

  void Simulate();

 private:
  std::unique_ptr<DealerStrategy> dealer_strategy_;
  std::vector<Seat> seats_;
};

}  // namespace bjmc

#endif // TABLE_H
