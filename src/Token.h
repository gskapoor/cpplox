#ifndef TOKEN_H
#define TOKEN_H
#pragma once

#include <optional>
#include <string>
#include <variant>
#include <any>

// Saw this in someone else's implementation
// using OptionalLiteral = std::optional<Literal>;

enum class TokenType{

  // Single-character tokens
  LEFT_PAREN, RIGHT_PAREN,
  LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS,
  SEMICOLON, SLASH, STAR,

  // One or Two Character tokens
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals
  IDENTIFIER, STRING, NUMBER,

  // Keywords
  AND, CLASS, ELSE, TRUE, FALSE, FUN, FOR,
  IF, NIL, OR, PRINT, RETURN, SUPER, THIS, VAR, WHILE,

  // End of File, I don't know why yet :)
  LOX_EOF

};

class Token{
  public:
    Token(TokenType p_type, std::string p_lexeme, 
      std::any p_literal, int p_line);

    Token(TokenType p_type, std::string p_lexeme, int p_line);

    TokenType getType() const {return type;};
    std::string getTypeString() const;

    int getLine() const {return line;};
    std::string getLexeme() const {return lexeme;};
    std::any getLiteral() const {return literal;};

    std::string toString() const;
    std::string literalToString() const;

  private:
    TokenType type;
    std::string lexeme;
    std::any literal;
    int line = -1;

};

#endif