#ifndef SHAKE_SORT_H_
#define SHAKE_SORT_H_

#include "sort_method.h"

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

#endif // SHAKE_SORT_H_