#include "src/Token.h"

#include <map>

auto TokenTypeString(const TokenType value){

  static const std::map<TokenType, std::string> lookUpTable{
    {TokenType::LEFT_PAREN, "LEFT_PAREN"},
    {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
    {TokenType::LEFT_BRACE, "LEFT_BRACE"},
    {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
    {TokenType::COMMA, "COMMA"},
    {TokenType::DOT, "DOT"},
    {TokenType::SEMICOLON, "SEMICOLON"},
    {TokenType::SLASH, "SLASH"},
    {TokenType::STAR, "STAR"},
    {TokenType::BANG, "BANG"},
    {TokenType::BANG_EQUAL, "BANG_EQUAL"},
    {TokenType::EQUAL, "EQUAL"},
    {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
    {TokenType::GREATER, "GREATER"},
    {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
    {TokenType::LESS, "LESS"},
    {TokenType::LESS_EQUAL, "LESS_EQUAL"},
    {TokenType::MINUS, "MINUS"},
    {TokenType::PLUS, "PLUS"},
    {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::STRING, "STRING"},
    {TokenType::NUMBER, "NUMBER"},
    {TokenType::AND, "AND"},
    {TokenType::CLASS, "CLASS"},
    {TokenType::ELSE, "ELSE"},
    {TokenType::FALSE, "FALSE"},
    {TokenType::FUN, "FUN"},
    {TokenType::FOR, "FOR"},
    {TokenType::IF, "IF"},
    {TokenType::NIL, "NIL"},
    {TokenType::OR, "OR"},
    {TokenType::PRINT, "PRINT"},
    {TokenType::RETURN, "RETURN"},
    {TokenType::SUPER, "SUPER"},
    {TokenType::THIS, "THIS"},
    {TokenType::TRUE, "TRUE"},
    {TokenType::VAR, "VAR"},
    {TokenType::WHILE, "WHILE"},
    {TokenType::LOX_EOF, "EOF"}};

  return lookUpTable.find(value)->second;
}

Token::Token(TokenType p_type, std::string p_lexeme, OptionalLiteral p_literal, int p_line)
  : type(p_type),
    lexeme(std::move(p_lexeme)),
    literal(std::move(p_literal)),
    line(p_line) {}

std::string Token::toString() const {
  std::string res = this->getTypeString() + " " + lexeme;
  if (literal.has_value()){
    res += " " + getLiteralString(literal.value());
  }
}

TokenType Token::getType() const {
  return type;
}

std::string Token::getTypeString() const {
  return TokenTypeString(type);
}

std::string Token::getLexeme() const {
  return lexeme;
}

OptionalLiteral Token::getLiteral() const {
  return literal;
}
