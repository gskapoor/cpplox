#include "src/Scanner.h"

Scanner::Scanner(std::string p_source)
  :source(p_source){}

std::vector<Token> Scanner::scanTokens() {

  while (!isAtEnd()) {
    start = current;
    // scanToken();
  }

  tokens.emplace_back(new Token(
    TokenType::LOX_EOF, "", std::nullopt, line ));

  return tokens;
}

bool Scanner::isAtEnd() {
  return current >= source.size();
}