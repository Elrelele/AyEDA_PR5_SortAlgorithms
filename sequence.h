/**
  Author: Leandro Delli Santi
  Date: 23/03/25
  Grade: Informatic engineer
  Mail: alu0101584003@ull.edu.es
  File: Definition and Declaration of Sequence class
*/

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include <iostream>

template <class Key>
class Sequence {
  public:
    virtual ~Sequence() = default;
    virtual Key& operator[](const size_t&) = 0;
    virtual const Key& operator[](const size_t&) const = 0;
};

#endif