#ifndef MONEY_H_
#define MONEY_H_

#include <cstdint>
#include <iosfwd>

class Money {
 public:
  Money();
  explicit Money(unsigned int rubles);
  Money(unsigned int rubles, std::int16_t kopeks);

  unsigned int rubles() const;
  std::int16_t kopeks() const;

  Money AddKopeks(unsigned int amount) const;

  Money& operator++();
  Money operator++(int);
  Money& operator--();
  Money operator--(int);

  explicit operator unsigned int() const;
  operator double() const;

  friend Money operator+(const Money& money, unsigned int amount);
  friend Money operator-(const Money& money, unsigned int amount);
  friend std::ostream& operator<<(std::ostream& output, const Money& money);

 private:
  static Money FromTotalKopeks(std::uint64_t total_kopeks);

  unsigned int rubles_{0};
  std::int16_t kopeks_{0};
};

#endif
