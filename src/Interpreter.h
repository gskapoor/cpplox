#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Scanner.h"
#include <string>

class Interpreter {

  public:


    Interpreter();
    int runFile(const std::string path);
    void runRepl();
    void error(int line, std::string message);

  private:
    bool hadError = false;

    void interpret(const std::string& source);
    void report(int line, std::string where, std::string message);

};

#endif
