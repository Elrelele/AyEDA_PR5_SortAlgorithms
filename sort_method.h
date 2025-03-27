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

template <class Key>
class ShellSort : public SortMethod<Key> {
  public:
    ShellSort(StaticSequence<Key>& array, double alpha) : alpha_{alpha}, SortMethod<Key>{&array} {}
    void Sort(Trace&);

    double GetAlpha() const { return alpha_; }

  private:
    double alpha_;
};

template <class Key>
void ShellSort<Key>::Sort(Trace& trace) {
  size_t size = this->array_->GetSize();
  trace.ShowMessage("\nThe sequence to order will be: ");
  trace.ShowSequence(*this->array_);

  for (int gap = size / 2; gap > 0; gap *= alpha_) {
    trace.ShowMessage("\nCurrent gap: " + std::to_string(gap));
    for (int i = gap; i < size; i++) {
      Key temp = (*this->array_)[i];
      int j;
      for (j = i; j >= gap && (*this->array_)[j - gap] > temp; j -= gap) {
        (*this->array_)[j] = (*this->array_)[j - gap];
      }
      (*this->array_)[j] = temp;
      
      trace.ShowMessage("Iteration " + std::to_string(i) + ":");
      trace.ShowSequenceIfEnabled(*this->array_);
    }
  }

  trace.ShowMessage("\nThe sorted sequence is: ");
  trace.ShowSequence(*this->array_);
}

#endif