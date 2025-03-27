/**
  Author: Leandro Delli Santi
  Date: 23/03/25
  Grade: Informatic engineer
  Mail: alu0101584003@ull.edu.es
  File: Definition of Nif class
*/

#include "nif.h"
#include <cmath>

constexpr size_t NIF_SIZE = 8;

NIF::NIF() {
  nif_ = (rand() % 90000000) + 10000000;
}

NIF::NIF(long number) {
  nif_ = number % max_digits;
}

long NIF::operator[](int index) const {
  return (nif_ / static_cast<int>(std::pow(10, index))) % 10;
}

bool NIF::operator==(const NIF& number) const {
  return this->nif_ == number.nif_;
}

bool NIF::operator!=(const NIF& number) const {
  return this->nif_ != number.nif_;
}

bool NIF::operator<(const NIF& number) const {
  return this->nif_ < number.nif_;
}

bool NIF::operator>(const NIF& number) const {
  return this->nif_ > number.nif_;
}

size_t NIF::Size() const {
  return NIF_SIZE;
}

std::istream& operator>>(std::istream& stream, NIF& number) {
  long input;
  stream >> input;
  number = NIF(input);
  return stream;
}

NIF::operator long() const {
  return this->nif_;
}