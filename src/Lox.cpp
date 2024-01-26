#include <vector>
#include <iostream>
#include <fstream>

#include "AstPrinter.h"
#include "Lox.h"
#include "Scanner.h"
#include "Parser.h"

using namespace Error;

std::vector<Token> scan (const std::string& source){
  Scanner scanner(source);

  std::vector<Token> tokensVec = scanner.scanTokens();

  return tokensVec;
}

Lox::Lox() {}

int Lox::runFile(std::string path) {

  std::ifstream inputFile(path);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file: " << path << std::endl;
    // TODO:  Find correct error code
    return 65;
  }

  std::string fileContent(
    (std::istreambuf_iterator<char>(inputFile)),
    (std::istreambuf_iterator<char>())
  );
  inputFile.close();

  std::cout << "File Content" << std::endl;
  interpret(fileContent);
  // DATA ERROR
  if (hadError) return 65;

  return 0;
}

void Lox::runRepl(){
  std:: cout << "> " ;
  std::string line;

  while(std::getline(std::cin, line) && !line.empty()) {
    interpret(line);

    hadError = false;
    std::cout << "> ";
  }
}

void Lox::interpret(const std::string& source){

  std::vector<Token> tokens = scan(source); 
  for (Token t : tokens){
    std::cout << t.toString() << std::endl;
  }
  Parser parser(tokens);
  std::unique_ptr<Expr> expr = std::move(parser.parse());

  AstPrinter a;

  std::cout << (a.toString(expr)) << std::endl;
  
}

namespace Error 
{
  std::vector<ErrorInfo> exceptionlist{};
  bool hadError = false;
  bool hadRuntimeError = false;

  void addError(unsigned int line, std::string where, std::string message) noexcept {
    exceptionList.emplace_back(line, std::move(where), std::move(message));
    hadError = true;
  }

  void addError(const Token& token, std::string message) noexcept {
    if (token.getType() == TokenType::LOX_EOF){
      exceptionList.emplace_back(token.getLine(), "at end", std::move(message));
    }
  }

  void report() noexcept {
    for (const auto& exception : exceptionList){
    std::cerr << "[Line: " << exception.line << "] Error" << exception.where << ": " << exception.message << std::endl;
    }
  }

}
