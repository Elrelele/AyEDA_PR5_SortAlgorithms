#ifndef STATIC_SEQUENCE_H_
#define STATIC_SEQUENCE_H_

#include "sequence.h"

template <class Key>
class StaticSequence : public Sequence<Key> {
  public:
    StaticSequence(size_t size);
    ~StaticSequence() { delete[] data_; }

    size_t GetSize() const;

    Key& operator[](const size_t&);
    const Key& operator[](const size_t&) const;

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

#endif // STATIC_SEQUENCE_H_