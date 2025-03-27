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

template <class Key>
class StaticSequence : public Sequence<Key> {
  public:
    StaticSequence(size_t size);
    ~StaticSequence() { delete[] data_; }

    size_t GetSize() const;

    Key& operator[](const size_t&);
    const Key& operator[](const size_t&) const;
    // void set(size_t, Key);

  private:
    Key* data_; 
    size_t size_;
};

template <class Key>
StaticSequence<Key>::StaticSequence(size_t size) : size_{size} {
  data_ = new Key[size_];
}

template <class Key>
size_t StaticSequence<Key>::GetSize() const {
  return size_;
}

template <class Key>
Key& StaticSequence<Key>::operator[](const size_t& index) {
  return data_[index];
}

template <class Key>
const Key& StaticSequence<Key>::operator[](const size_t& index) const {
  return data_[index];
}

// template <class Key>
// void StaticSequence<Key>::set(size_t index, Key value) {
//   data_[index] = value;
// }

#endif