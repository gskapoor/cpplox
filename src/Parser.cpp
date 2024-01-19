#include <iostream>

#include "Parser.h"
#include "Expr.h"
#include "Token.h"

Parser::Parser(std::vector<Token> tokens) : tokens(tokens)
{}

std::unique_ptr<Expr> Parser::parse() {
  try {
    return expression();
  } catch (ParseError error){
    return nullptr;
  }
}

std::unique_ptr<Expr> Parser::expression() {
  return comma();
}

std::unique_ptr<Expr> Parser::comma() {
  std::unique_ptr<Expr> expr = ternary();

  while (match({TokenType::COMMA})){
    Token op = previous();

    std::unique_ptr<Expr> right = ternary();
    expr = std::make_unique<BinaryExpr>(
      std::move(expr), op, std::move(right)
    );
  }

  return expr;

}

std::unique_ptr<Expr> Parser::ternary(){
  std::unique_ptr<Expr> expr = equality();

  if (match({TokenType::QUESTION})){
    std::unique_ptr<Expr> middle = expression();
    consume(TokenType::COLON, "Expect ':' in ternary operator ");
    std::unique_ptr<Expr> right = equality();
    expr = std::make_unique<TernaryExpr>(
      std::move(expr), std::move(middle), std::move(right)
    );
  }

  return expr;
}

std::unique_ptr<Expr> Parser::equality() {
  std::unique_ptr<Expr> expr = comparison();

  while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {

    Token op = previous();

    std::unique_ptr<Expr> right = comparison();
    expr = std::make_unique<BinaryExpr>(
      std::move(expr), op, std::move(right)
    );
  }

  return expr;
}

std::unique_ptr<Expr> Parser::comparison() {

  std::unique_ptr<Expr> expr = term();

  while(match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})){
    Token op = previous();
    std::unique_ptr<Expr> right = term();
    expr = std::make_unique<BinaryExpr>(
      std::move(expr), op, std::move(right)
    );
  }
  return expr;
}

std::unique_ptr<Expr> Parser::term() {

  std::unique_ptr<Expr> expr = factor();

  while(match({TokenType::MINUS, TokenType::PLUS})){
    Token op = previous();
    std::unique_ptr<Expr> right = factor();
    expr = std::make_unique<BinaryExpr>(
      std::move(expr), op, std::move(right)
    );
  }
  return expr;
}

std::unique_ptr<Expr> Parser::factor() {

  std::unique_ptr<Expr> expr = unary();

  while(match({TokenType::SLASH, TokenType::STAR})){
    Token op = previous();
    std::unique_ptr<Expr> right = unary();
    expr = std::make_unique<BinaryExpr>(
      std::move(expr), op, std::move(right)
    );
  }
  return expr;
}

std::unique_ptr<Expr> Parser::unary() {

  if (match({TokenType::MINUS, TokenType::BANG})){
    Token op = previous();
    std::unique_ptr<Expr> right = unary();
    return std::make_unique<UnaryExpr>(
      op, std::move(right)
    );
  }
  return primary();
}

std::unique_ptr<Expr> Parser::primary() {
  if (match({TokenType::FALSE})) return std::make_unique<LiteralExpr>(false);
  if (match({TokenType::TRUE})) return std::make_unique<LiteralExpr>(true);
  if (match({TokenType::NIL})) return std::make_unique<LiteralExpr>(std::any{});

  if (match({TokenType::NUMBER, TokenType::STRING})){
    return std::make_unique<LiteralExpr>(previous().getLiteral());
  }

  if (match({TokenType::LEFT_PAREN})){
    std::unique_ptr<Expr> expr = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after expression, ");
    return std::make_unique<GroupExpr>(std::move(expr));
  }

  throw error(peek(), "Expect expression.");
}

void Parser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (previous().getType() == TokenType::SEMICOLON) return;

    switch (peek().getType()) {
      case TokenType::CLASS:
      case TokenType::FUN:
      case TokenType::VAR:
      case TokenType::FOR:
      case TokenType::IF:
      case TokenType::WHILE:
      case TokenType::PRINT:
      case TokenType::RETURN:
        return;
    }

    advance();
  }
}

bool Parser::match(std::initializer_list<TokenType> types) {
  for (TokenType type: types){
    if (check(type)) {
      advance();
      return true;
    }
  }

  return false;
}

bool Parser::check(TokenType type){
  if (isAtEnd()) return false;

  return peek().getType() == type;
}

Token Parser::advance() {
  if (!isAtEnd()) current++;
  return previous();
}

bool Parser::isAtEnd() {
  return peek().getType() == TokenType::LOX_EOF;
}

Token Parser::peek() {
  return tokens.at(current);
}

Token Parser::previous() {
  return tokens.at(current - 1);
}

Token Parser::consume(TokenType type, const std::string& message) {
  if (check(type)) return advance();

  throw error(peek(), message);
}

ParseError Parser::error(const Token& token, const std::string& message){
  // TODO: Add actual error handling
  std::cerr << token.toString() << ": " << message << std::endl;

  return {};
}



