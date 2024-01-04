#include <iostream>
#include <fstream>
#include <string>

#include "Lox.h"

int main(int argc, char* argv[]) {

  Lox interpreter;
  if (argc > 2){
    std::cerr << "Usage: " << argv[0] << " <script> " << std::endl;

    return 64;
  } else if (argc == 2){
    return interpreter.runFile(argv[1]);
  } 
  
  interpreter.runRepl();

  return 0;
}
