#ifndef SORT_METHOD_H_
#define SORT_METHOD_H_

#include "sequence.h"
#include "trace.h"

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

template <class Key>
class ShakeSort : public SortMethod<Key> {
  public:
    ShakeSort(StaticSequence<Key>& array) : SortMethod<Key>{&array} {}
    void Sort(Trace&);
};

template <class Key>
void ShakeSort<Key>::Sort(Trace& trace) {
  size_t begin = 1; // Start from the second element
  size_t size = this->array_->GetSize();
  size_t end = size - 1; // Start from the last element
  size_t last_swap_index = size; // Track the last index where a swap occurred

  trace.ShowMessage("\nThe sequence to order will be: ");
  trace.ShowSequence(*this->array_);

  while (begin < end) {

    // left to right pass
    for (int i = end; i >= begin; --i) {
      if ((*this->array_)[i] < (*this->array_)[i - 1]) {
        std::swap((*this->array_)[i - 1], (*this->array_)[i]); // Swap elements
        last_swap_index = i; // Update the last swapped index
      }
    }
    begin = last_swap_index + 1;  // Update the starting index

    trace.ShowMessage("");
    trace.ShowMessage("After left to right pass:");
    trace.ShowSequenceIfEnabled(*this->array_); 

    // Right to left pass
    for (int i = begin; i <= end; ++i) {
      if ((*this->array_)[i] < (*this->array_)[i - 1]) {
        std::swap((*this->array_)[i - 1], (*this->array_)[i]); // Swap elements
        last_swap_index = i;  // Update the last swapped index
      }
    }
    end = last_swap_index - 1;  // Update the ending index

    trace.ShowMessage("");
    trace.ShowMessage("After right to left pass:");
    trace.ShowSequenceIfEnabled(*this->array_); 
  }

  trace.ShowMessage("\nThe sorted sequence is: ");
  trace.ShowSequence(*this->array_);
}

template <class Key>
class QuickSort : public SortMethod<Key> { 
  public:
    QuickSort(StaticSequence<Key>& array) : SortMethod<Key>{&array} {}
    void Sort(Trace&);

    void QuickSortRecursive(int, int, Trace&);

  private:
    size_t Partition(int, int);
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

// template <class Key>
// class HeapSort : public SortMethod<Key> {
//   public:
//     HeapSort(StaticSequence<Key>& array) : SortMethod<Key>{&array} {}
//     void Sort(Trace&);
// };

// template <class Key>
// class ShellSort : public SortMethod<Key> {
//   public:
//     ShellSort(StaticSequence<Key>& array) : SortMethod<Key>{&array} {}
//     void Sort(Trace&);
// };

#endif