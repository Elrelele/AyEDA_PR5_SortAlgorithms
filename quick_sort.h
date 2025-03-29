#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

#include "sort_method.h"

template <class Key>
class QuickSort : public SortMethod<Key> { 
  public:
    QuickSort(StaticSequence<Key>& array) : SortMethod<Key>{&array} {}
    void Sort(Trace&);

    void QuickSortRecursive(int, int, Trace&);
};

template <class Key>
void QuickSort<Key>::Sort(Trace& trace) {
  trace.ShowMessage("\nThe sequence to order will be: ");
  trace.ShowSequence(*this->array_);
  
  QuickSortRecursive(0, this->array_->GetSize() - 1, trace);

  trace.ShowMessage("\nThe sorted sequence is: ");
  trace.ShowSequence(*this->array_);
}

template <class Key>
void QuickSort<Key>::QuickSortRecursive(int begin, int end, Trace& trace) {
  size_t i = begin;
  size_t j = end;
  Key pivot = (*this->array_)[(i + j) / 2];

  trace.ShowMessage("\nPivot chosen: " + std::to_string(pivot));

  while (i <= j) {
    while ((*this->array_)[i] < pivot) i++;
    while ((*this->array_)[j] > pivot) j--;
    if (i <= j) {
      trace.ShowMessage("Swapping elements " + std::to_string((*this->array_)[i]) + " and " + std::to_string((*this->array_)[j]));
      std::swap((*this->array_)[i], (*this->array_)[j]);
      i++;
      j--;
    }
  }
  
  trace.ShowSequenceIfEnabled(*this->array_);

  if (begin < j) QuickSortRecursive(begin, j, trace);
  if (i < end) QuickSortRecursive(i, end, trace);
}

#endif