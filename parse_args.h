/*
  Author: Leandro Delli Santi
  E-Mail: alu0101584003@ull.edu.es
  Grade: Informatic engineer
  University: University of La Laguna (ULL)
  Date: 24/03/25
  File: Parse_arguments Declaration
*/

#ifndef PARSE_ARGS_H_
#define PARSE_ARGS_H_

#include <iostream>
#include <stdexcept>

enum class InsertType {
  MANUAL,
  RANDOM,
  FILE
};

struct Args {
  size_t size = 0;
  int ord = 0;
  InsertType insert_method;
  std::string filename;
  bool trace = false;
};

const std::invalid_argument kSizeNot("Error: size not provided");
const std::invalid_argument kOrdNot("Error: Code that identifies de sort method not provided");
const std::invalid_argument kInsertMethodNot("Error: insert method not provided");
const std::invalid_argument kFilenameNot("Error: filename not provided");
const std::invalid_argument ktraceNot("Error: trace not provided");

Args ParseArguments(const int argc, const char** argv);

#endif