#include "hand.h"

void Hand::ComputeValues() const noexcept {
  int total = 0;
  int ace_seen = false;
  for (const auto card : cards_) {
    auto val = card.Value();
    if (val == 1) ace_seen = true;
    total += card.Value();
  }
  is_soft_ = false;
  if (ace_seen) {
    if (total + 10 <= 21) {
      is_soft_ = true;
      total += 10;
    }
  }
  total_ = total;
  values_valid_ = true;
}

int Hand::Value() const noexcept {
  if (!values_valid_) {
    ComputeValues();
  }
  return total_;
}

bool Hand::IsSoft() const noexcept {
  if (!values_valid_) {
    ComputeValues();
  }
  return is_soft_;
}