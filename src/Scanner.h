#ifndef SCANNER_H
#define SCANNER_H
#pragma once

#include <vector>

#include "src/Token.h"

class Scanner {
  public:
    Scanner(std::string p_source);
    std::vector<Token> scanTokens();

  private:
    std::string source;
    std::vector<Token> tokens;

    int start = 0;
    int current = 0;
    int line = 1;

    char advance();
    void addToken(TokenType t);
    void identifier();
    bool isAtEnd();
    bool match(char expected);
    void number();
    char peek();
    char peekNext();
    void scanToken();
    void string();

};

#endif ;