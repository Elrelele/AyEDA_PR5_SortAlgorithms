#ifndef SORT_METHOD_H_
#define SORT_METHOD_H_

#include "sequence.h"
#include "trace.h"

#include <cstddef>

template <class Key>
class SortMethod {
  public:
    SortMethod(StaticSequence<Key>* array) : array_(array) {}
    virtual ~SortMethod() = default;
  
    virtual void Sort(Trace&) = 0;

  protected:
    StaticSequence<Key>* array_;
};

template <class Key>
class InsertionSort : public SortMethod<Key> {
  public:
    InsertionSort(StaticSequence<Key>& array) : SortMethod<Key>{&array} {}
    void Sort(Trace&);
};

template <class Key>
void InsertionSort<Key>::Sort(Trace& trace) {
  trace.ShowMessage("\nThe sequence to order will be: ");
  trace.ShowSequence(*this->array_);

  for (int i = 1; i < this->array_->GetSize(); ++i) {
    int j = i - 1;
    Key x = (*this->array_)[i];
    
    trace.ShowMessage("");
    trace.ShowMessage("Iteration " + std::to_string(i) + ":");
    
    while (j >= 0 && (*this->array_)[j] > x) {
      (*this->array_)[j + 1] = (*this->array_)[j]; 
      j--;
    }
    (*this->array_)[j + 1] = x; 

    trace.ShowSequenceIfEnabled(*this->array_);
  }
  trace.ShowMessage("\nThe sorted sequence is: ");
  trace.ShowSequence(*this->array_);
}

// template <class Key>
// class ShakeSort {
//   public:
//     void sort();
// };

// template <class Key>
// class QuickSort {
//   public:
//     void sort();
// };

// template <class Key>
// class HeapSort {
//   public:
//     void sort();
// };

// template <class Key>
// class ShellSort {
//   public:
//     void sort();
// };

#endif