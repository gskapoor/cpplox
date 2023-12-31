#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Scanner.h"
#include <string>

class Interpreter {

  public:

    Interpreter();
    void runFile(const std::string path);
    void runRepl();

  private:
    void interpret(const std::string& source);

};

#endif
