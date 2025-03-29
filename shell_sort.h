#ifndef SHELL_SORT_H_
#define SHELL_SORT_H_

#include "sort_method.h"

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

#endif // SHELL_SORT_H