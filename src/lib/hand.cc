#include "absl/strings/str_join.h"

#include "hand.h"

namespace bjmc {

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
  InvalidateValues();
}

void Hand::AddCard(Card card) noexcept {
  cards_.emplace_back(std::move(card));
  InvalidateValues();
}

Hand Hand::Split() noexcept {
  assert(Size() == 2);

  Hand other;
  other.AddCard(cards_.back());
  cards_.pop_back();
  InvalidateValues();
  return other;
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

std::string Hand::ToString() const noexcept {
  const auto str = absl::StrJoin(
      cards_, " ",
      [](std::string* out, const Card& card) { out->append(card.ToString()); });
  return absl::StrCat(str, "-> ", std::to_string(Value()));
}

}  // namespace bjmc
