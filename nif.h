/**
  Author: Leandro Delli Santi
  Date: 23/03/25
  Grade: Informatic engineer
  Mail: alu0101584003@ull.edu.es
  File: Declaration of Nif class
*/

#ifndef NIF_H_
#define NIF_H_

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <istream>

constexpr int max_digits = 100000000;

class NIF {
  public:
    NIF();
    NIF(long);
    
    long operator[](int) const;

    bool operator==(const NIF&) const;
    bool operator!=(const NIF&) const;
    bool operator<(const NIF&) const;
    bool operator>(const NIF&) const;
    
    size_t size() const;

    friend std::istream& operator>>(std::istream&, NIF&);
    
    operator long() const;
  
  private:
    long nif_;
};

std::istream& operator>>(std::istream&, NIF&);

#endif