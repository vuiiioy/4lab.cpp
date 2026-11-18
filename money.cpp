#include "money.h"

#include <iomanip>
#include <limits>
#include <ostream>
#include <stdexcept>

Money::Money() : rubles_{0}, kopeks_{0} {}

Money::Money(unsigned int rubles) : rubles_{rubles}, kopeks_{0} {}

Money::Money(unsigned int rubles, std::int16_t kopeks)
    : rubles_{rubles}, kopeks_{kopeks} {
  if (kopeks < 0 || kopeks > 99) {
    throw std::invalid_argument("Допустимое количество копеек: от 0 до 99.");
  }
}

unsigned int Money::rubles() const { return rubles_; }

std::int16_t Money::kopeks() const { return kopeks_; }

Money Money::AddKopeks(unsigned int amount) const { return *this + amount; }

Money& Money::operator++() {
  *this = *this + 1U;
  return *this;
}

Money Money::operator++(int) {
  Money previous{*this};
  ++(*this);
  return previous;
}

Money& Money::operator--() {
  *this = *this - 1U;
  return *this;
}

Money Money::operator--(int) {
  Money previous{*this};
  --(*this);
  return previous;
}

Money::operator unsigned int() const { return rubles_; }

Money::operator double() const { return static_cast<double>(kopeks_) / 100.0; }

Money operator+(const Money& money, unsigned int amount) {
  const std::uint64_t total_kopeks{static_cast<std::uint64_t>(money.rubles_) *
                                       100U +
                                   static_cast<std::uint64_t>(money.kopeks_) +
                                   static_cast<std::uint64_t>(amount)};
  return Money::FromTotalKopeks(total_kopeks);
}

Money operator-(const Money& money, unsigned int amount) {
  const std::uint64_t total_kopeks{static_cast<std::uint64_t>(money.rubles_) *
                                       100U +
                                   static_cast<std::uint64_t>(money.kopeks_)};
  if (static_cast<std::uint64_t>(amount) > total_kopeks) {
    throw std::underflow_error("Нельзя вычесть больше копеек, чем имеется.");
  }
  return Money::FromTotalKopeks(total_kopeks -
                                static_cast<std::uint64_t>(amount));
}

std::ostream& operator<<(std::ostream& output, const Money& money) {
  const char previous_fill{output.fill('0')};
  output << money.rubles_ << ',' << std::setw(2) << money.kopeks_ << " руб.";
  output.fill(previous_fill);
  return output;
}

Money Money::FromTotalKopeks(std::uint64_t total_kopeks) {
  const std::uint64_t rubles{total_kopeks / 100U};
  if (rubles > std::numeric_limits<unsigned int>::max()) {
    throw std::overflow_error(
        "Результат превышает максимально допустимое количество рублей.");
  }
  return Money(static_cast<unsigned int>(rubles),
               static_cast<std::int16_t>(total_kopeks % 100U));
}
