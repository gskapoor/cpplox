#include <vector>
#include <iostream>
#include <fstream>

#include "Interpreter.h"
#include "Scanner.h"

std::vector<Token> scan (const std::string& source){
  Scanner scanner(source);

  std::vector<Token> tokensVec = scanner.scanTokens();

  return tokensVec;
}

Interpreter::Interpreter() {}

int Interpreter::runFile(std::string path) {

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

void Interpreter::runRepl(){
  std:: cout << "> " ;
  std::string line;

  while(std::getline(std::cin, line) && !line.empty()) {
    interpret(line);

    hadError = false;
    std::cout << "> ";
  }
}

void Interpreter::interpret(const std::string& source){

  std::vector<Token> tokens = scan(source); 

  for (Token token: tokens){
    std::cout << token.toString() << std::endl;
  }
}

void Interpreter::report(int line, std::string where, std::string message){
  std::cerr << "[Line: " << line << "] Error" << where << ": " << message << std::endl;
}

void Interpreter::error(int line, std::string message) {
  report(line, "", message);
}
