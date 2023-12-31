#include <iostream>
#include <fstream>
#include <string>

#include "Interpreter.h"

int main(int argc, char* argv[]) {

  Interpreter interpreter;
  if (argc > 2){
    std::cerr << "Usage: " << argv[0] << " <script> " << std::endl;
    return 64;
  } else if (argc == 2){
    interpreter.runFile(argv[1]);
  } else {
    interpreter.runRepl();
  }

  return 0;
}
