#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Scanner.h"
#include <string>

class Interpreter {

  public:

    Interpreter();
    int runScript(const std::string fileLocation);
    void runRepl();

  private:
    Scanner s;

    void interpret(const std::string& source);

};

#endif