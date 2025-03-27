#ifndef TRACE_H_
#define TRACE_H_

#include <iostream>

#include "sequence.h"

class Trace {
  public:
    Trace(bool enable) : enable_(enable) {}
  
    void ShowMessage(const std::string& message) const {
      if (enable_) 
        std::cout << message << std::endl;
    }
    
    template <class Key>
    void ShowSequenceIfEnabled(const StaticSequence<Key>& array) const {
      if (enable_) {
        for (std::size_t i = 0; i < array.GetSize(); ++i) 
          std::cout << array[i] << " ";
        std::cout << std::endl;
      }
    }

    template <class Key>
    void ShowSequence(const StaticSequence<Key>& array) const {
      for (std::size_t i = 0; i < array.GetSize(); ++i) 
        std::cout << array[i] << " ";
      std::cout << std::endl;
    }

  private:
    bool enable_; 
};

#endif