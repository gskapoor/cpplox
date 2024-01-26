#ifndef LOX_H
#define LOX_H 

#include "Scanner.h"
#include <string>

class Lox {

  public:


    Lox();
    int runFile(const std::string path);
    void runRepl();

  private:

    void interpret(const std::string& source);

};

namespace Error 
{
  struct ErrorInfo{
    const unsigned int line;
    const std::string where;
    const std::string message;

    ErrorInfo(unsigned int line, std::string where, std::string message)
      : line{line}, where{std::move(where)}, message{std::move(message)}{}
  };

    void report() noexcept;

    // TODO: ADD THIS
    // void addRuntimeError(const RuntimeError& error) noexcept;

    void addError(unsigned int line, std::string where, std::string message) noexcept;

    void addError(const Token& token, std::string message) noexcept;

    extern bool hadError;
    extern bool hadRuntimeError;
    extern std::vector<ErrorInfo> exceptionList;
}

#endif
