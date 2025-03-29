#ifndef INSERTION_SORT_H_
#define INSERTION_SORT_H_

#include "sort_method.h"

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

#endif