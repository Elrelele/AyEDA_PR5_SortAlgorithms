/*
  Author: Leandro Delli Santi
  E-Mail: alu0101584003@ull.edu.es
  Grade: Informatic engineer
  University: University of La Laguna (ULL)
  Date: 24/03/25
  File: Definition of parse_arguments
*/

#include "parse_args.h"

Args ParseArguments(const int argc, const char** argv) {
  
  Args args;
  bool size = false, ord = false, init = false, trace = false;
  
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-size" && i + 1 < argc) {
      size = true;
      args.size = std::stoi(argv[++i]);
    } else if (arg == "-ord" && i + 1 < argc) {
      ord = true;
      args.ord = std::stoi(argv[++i]);
    } else if (arg == "-init" && i + 1 < argc) {
      init = true;
      std::string initArg = argv[++i];
      if (initArg == "manual") {
        args.insert_method = InsertType::MANUAL;
      } else if (initArg == "random") {
        args.insert_method = InsertType::RANDOM;
      } else if (initArg == "file") {
        if (i + 1 >= argc || argv[i + 1][0] == '-') {
          throw kFilenameNot;
        }
        args.insert_method = InsertType::FILE;
        args.filename = argv[++i];
      }
    } else if (arg == "-trace" && i + 1 < argc) {
      trace = true;
      std::string traceArg = argv[++i];
      if (traceArg == "y") args.trace = true;
    }
  }

  if (!size) 
    throw kSizeNot;
  if (!ord) 
    throw kOrdNot;
  if (!init) 
    throw kInsertMethodNot;
  if (!trace) 
    throw ktraceNot;

  return args;
}