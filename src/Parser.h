#ifndef PARSER_H
#define PARSER_H
#pragma once

#include <vector>
#include <initializer_list>

#include "Expr.h"

struct ParseError : std::exception {};

class Parser {
  public:

  Parser(std::vector<Token> tokens);
  std::unique_ptr<Expr> parse();

  private:

  std::vector<Token> tokens;
  int current = 0;

  std::unique_ptr<Expr> comma(); 
  std::unique_ptr<Expr> comparison();
  std::unique_ptr<Expr> expression();
  std::unique_ptr<Expr> equality();
  std::unique_ptr<Expr> factor();
  std::unique_ptr<Expr> primary();
  std::unique_ptr<Expr> ternary();
  std::unique_ptr<Expr> term();
  std::unique_ptr<Expr> unary();

  bool match(std::initializer_list<TokenType> types);
  bool check(TokenType type);
  bool isAtEnd();

  Token advance();
  Token peek();
  Token previous();
  Token consume(const TokenType type,const std::string& message );

  static ParseError error(const Token& token, const std::string& message);

  void synchronize();

};

#endif