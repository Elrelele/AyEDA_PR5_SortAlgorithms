#ifndef SORT_METHOD_H_
#define SORT_METHOD_H_

#include "trace.h"
#include "static_sequence.h"

#include <cstddef>
#include <algorithm>
#include <utility>

template <class Key>
class SortMethod {
  public:
    SortMethod(StaticSequence<Key>* array) : array_(array) {}
    virtual ~SortMethod() = default;
  
    virtual void Sort(Trace&) = 0;

  protected:
    StaticSequence<Key>* array_;
};

#endif