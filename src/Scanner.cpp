#include <iostream>
#include <map>

#include "Scanner.h"

bool isDigit(char c){
  return c >= '0' && c <= '9';
}

bool isAlpha(char c){
  return (c >= 'a') && (c <= 'z') ||
    (c >= 'A') && (c <= 'Z') ||
    c == '_';
}

bool isAlphaNumeric(char c){
  return isAlpha(c) || isDigit(c);
}

auto ReservedOrIdentifier(const std::string& str) -> TokenType {
  static const std::map<std::string, TokenType> lookUpTable{
      {"and", TokenType::AND},       {"class", TokenType::CLASS},
      {"else", TokenType::ELSE},     {"false", TokenType::FALSE},
      {"fun", TokenType::FUN},       {"for", TokenType::FOR},
      {"if", TokenType::IF},         {"nil", TokenType::NIL},
      {"or", TokenType::OR},         {"print", TokenType::PRINT},
      {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
      {"this", TokenType::THIS},     {"true", TokenType::TRUE},
      {"var", TokenType::VAR},       {"while", TokenType::WHILE}};

  auto iter = lookUpTable.find(str);
  if (iter == lookUpTable.end()) {
    return TokenType::IDENTIFIER;
  }
  return iter->second;
}

Scanner::Scanner(std::string p_source)
  :source(p_source){}

char Scanner::advance() {
  return source.at(current++);
}

char Scanner::peek(){
  if (isAtEnd()) return '\0';
  return source.at(current);
}

char Scanner::peekNext() {
  if (current + 1 >= source.size()) return '\0';
  return source.at(current + 1);
}

void Scanner::addToken(TokenType type) {
  std::string text = source.substr(start, current - start);
  tokens.emplace_back(type, text, line);
}

void Scanner::addToken(TokenType type, std::any literal) {
  std::string text = source.substr(start, current - start);
  tokens.emplace_back(type, text, literal, line);
}

bool Scanner::match(char expected){
  if (isAtEnd()) return false;
  if (source.at(current) != expected) return false;

  current++;
  return true;
}

void Scanner::string(){
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') line++;
    advance();
  }

  if (isAtEnd()){
    std::cerr << "Line: " << line << " , Unterminated string." << std::endl;
    return;
  }

  advance();

  addToken(TokenType::STRING, source.substr(start + 1, current - start - 2));
}

void Scanner::number(){
  while(isDigit(peek())) advance();
  if (peek() == '.' && isDigit(peekNext())) {
    advance();

    while(isDigit(peek())) advance();
  }

  addToken(TokenType::NUMBER, std::stod(source.substr(start, current - start)));
}

void Scanner::identifier() {
  while (isAlphaNumeric(peek())) advance();

  std::string text = source.substr(start, current - start);
  TokenType type = ReservedOrIdentifier(text);
  addToken(type);
}

void Scanner::multiline() {
  while(!isAtEnd() && (peek() != '*' || peekNext() != '/')) advance();

  if (!isAtEnd()){
    advance();
    advance();
  }
  // TODO: throw error if is at end
}

void Scanner::scanToken() {
  char c = advance();
  switch (c)
  {
    case '(': addToken(TokenType::LEFT_PAREN); break;
    case ')': addToken(TokenType::RIGHT_PAREN); break;
    case '{': addToken(TokenType::LEFT_BRACE); break;
    case '}': addToken(TokenType::RIGHT_BRACE); break;
    case ',': addToken(TokenType::COMMA); break;
    case '.': addToken(TokenType::DOT); break;
    case '-': addToken(TokenType::MINUS); break;
    case '+': addToken(TokenType::PLUS); break;
    case ';': addToken(TokenType::SEMICOLON); break;
    case '*': addToken(TokenType::STAR); break;
    case '?': addToken(TokenType::QUESTION); break;
    case ':': addToken(TokenType::COLON); break;

    // One or Two character lexemes
    case '!':
      addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
      break;
    case '=':
      addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
      break;
    case '<':
      addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
      break;
    case '>':
      addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
      break;

    // Now for comments or division
    case '/':
      if (match('/')){
        while (peek() != '\n' && !isAtEnd()) advance();
      } else if (match('*')){
        multiline();
      } else {
        addToken(TokenType::SLASH);
      }
      break;
    case ' ':
    case '\r':
    case '\t':
      break;
    case  '\n':
      line++;
      break;
    case '"': string(); break;

    default:
      // TODO: Add an actual error reporter
      if (isDigit(c)){
        number();
      } else if (isAlpha(c)){
        identifier();
      } else {
        std::cerr << "[line " << line << "] Error: Unexpected char" << std::endl;
      }
      break;
  };
}

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.emplace_back(TokenType::LOX_EOF, "", std::nullopt, line );

  return tokens;
}

bool Scanner::isAtEnd() {
  return current >= source.size();
}
