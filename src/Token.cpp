#include "Token.h"

#include <map>
#include <any>

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
    {TokenType::SLASH, "QUESTION"},
    {TokenType::SLASH, "COLON"},
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

Token::Token(TokenType p_type, std::string p_lexeme, std::any p_literal, int p_line)
  : type(p_type),
    lexeme(std::move(p_lexeme)),
    literal(std::move(p_literal)),
    line(p_line) {}

Token::Token(TokenType p_type, std::string p_lexeme, int p_line)
  : type(p_type),
    lexeme(std::move(p_lexeme)),
    line(p_line)
{}

std::string Token::toString() const {
  std::string res = this->getTypeString() + " " + lexeme;
  if (literal.has_value()){
    res += " " + literalToString();
  }
  return res;
}

std::string Token::literalToString() const {

  switch (type) {
    case TokenType::STRING:
      return std::any_cast<std::string>(literal);
    case TokenType::NUMBER:
      return std::to_string(std::any_cast<double>(literal));
    default:
      return "";
  }

}

std::string Token::getTypeString() const {
  return TokenTypeString(type);
}

