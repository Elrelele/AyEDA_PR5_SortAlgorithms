#ifndef HEAP_SORT_H_
#define HEAP_SORT_H_

#include "sort_method.h"

template <class Key>
class HeapSort : public SortMethod<Key> {
  public:
    HeapSort(StaticSequence<Key>& array) : SortMethod<Key>{&array} {}
    void Sort(Trace&);

    void Heapify(int, int, Trace&);
};

template <class Key>
void HeapSort<Key>::Sort(Trace& trace) {
  size_t size = this->array_->GetSize();
  trace.ShowMessage("\nThe sequence to order will be: ");
  trace.ShowSequence(*this->array_);

  // Build heap (rearrange vector)
  for (int i = size / 2 - 1; i >= 0; i--) {
    trace.ShowMessage("\nHeapifying at index: " + std::to_string(i));
    Heapify(i, size, trace);
    trace.ShowSequenceIfEnabled(*this->array_);
  }

  // One by one extract an element from heap
  for (int i = size - 1; i > 0; i--) {
    trace.ShowMessage("Swapping root " + std::to_string((*this->array_)[0]) + " with " + std::to_string((*this->array_)[i]));
    std::swap((*this->array_)[0], (*this->array_)[i]);

    trace.ShowSequenceIfEnabled(*this->array_);
    
    // call max heapify on the reduced heap
    Heapify(0, i, trace);
  }

  trace.ShowMessage("\nThe sorted sequence is: ");
  trace.ShowSequence(*this->array_);
}

template <class Key>
void HeapSort<Key>::Heapify(int index, int size, Trace& trace) {
  int largest = index; // Initialize largest as root
  int left = 2 * index + 1; // left = 2*i + 1
  int right = 2 * index + 2; // right = 2*i + 2

  trace.ShowMessage("\nHeapifying subtree rooted at index: " + std::to_string(index));

  // If left child is larger than root
  if (left < size && (*this->array_)[left] > (*this->array_)[largest]) {
    largest = left;
  }

  // If right child is larger than largest so far
  if (right < size && (*this->array_)[right] > (*this->array_)[largest]) {
    largest = right;
  }

  // If largest is not root
  if (largest != index) {
    trace.ShowMessage("Swapping " + std::to_string((*this->array_)[index]) + " with " + std::to_string((*this->array_)[largest]));
    std::swap((*this->array_)[index], (*this->array_)[largest]);

    // Recursively heapify the affected sub-tree
    Heapify(largest, size, trace);
  }
}

#endif