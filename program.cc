/*
  Author: Leandro Delli Santi
  E-Mail: alu0101584003@ull.edu.es
  Grade: Informatic engineer
  University: University of La Laguna (ULL)
  Date: 24/03/25
  File: Main file of the program, all the testing and final result will be here
  Progress: 
    - 24/03/25 Creation of the files and structural details
    - 25/03/25 Advances and the certefication that InsertionSort works correctly
    - 27/03/25 Creation of the trace file and end of the project
*/

#include <ctime>
#include <iostream>
#include <fstream>

#include "parse_args.h"
#include "sort_method.h"
#include "insertion_sort.h"
#include "shake_sort.h"
#include "quick_sort.h"
#include "heap_sort.h"
#include "shell_sort.h"
#include "nif.h"
#include "trace.h"

int main(const int argc, const char** argv) {
  Args args = ParseArguments(argc, argv);
  size_t size = args.size;
  StaticSequence<NIF> seq(size);

  switch (args.insert_method) {
    case InsertType::MANUAL:
      std::cout << "Introduce " << args.size << " NIFs:" << std::endl;
      for (int i = 0; i < args.size; ++i) {
        NIF nifValue;
        std::cin >> nifValue;
        seq[i] = NIF(nifValue);
      }
    break;
    case InsertType::RANDOM:
      std::cout << args.size << " Random NIFs are being generated:" << std::endl;
      srand(time(NULL));
      for (int i = 0; i < args.size; ++i) {
        seq[i] = NIF();
      }  
    break;
    case InsertType::FILE:
      std::cout << "The numbers will be read from: " << args.filename << std::endl;
      std::ifstream input_file(args.filename);
      if (!input_file) {
        std::cerr << "Error: Could not open file " << args.filename << std::endl;
        return 1;
      }
      for (int i = 0; i < args.size; ++i) {
        NIF nifValue;
        input_file >> nifValue;  
        seq[i] = NIF(nifValue);
      }
      input_file.close();
    break;
  }

  SortMethod<NIF>* sorted_sequence = nullptr;
  switch (args.ord) {
    case 1: 
      sorted_sequence = new InsertionSort<NIF>(seq); 
    break;
    case 2: 
      sorted_sequence = new ShakeSort<NIF>(seq); 
    break;
    case 3: 
      sorted_sequence = new QuickSort<NIF>(seq); 
    break;
    case 4: 
      sorted_sequence = new HeapSort<NIF>(seq); 
    break;
    case 5: 
      sorted_sequence = new ShellSort<NIF>(seq, 0.5); 
    break; 
    default: throw std::runtime_error("Error: Algoritmo de ordenación no válido.");
  }

  Trace trace(args.trace);
  sorted_sequence->Sort(trace);

  delete sorted_sequence; 
  return 0;
}