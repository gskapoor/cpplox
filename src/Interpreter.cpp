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

void Interpreter::runFile(std::string path) {

  std::ifstream inputFile(path);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file: " << path << std::endl;
    return;
  }

  std::string fileContent(
    (std::istreambuf_iterator<char>(inputFile)),
    (std::istreambuf_iterator<char>())
  );
  inputFile.close();

  std::cout << "File Content" << std::endl;
  interpret(fileContent);
}

void Interpreter::runRepl(){
  std:: cout << "> " ;
  std::string line;

  while(std::getline(std::cin, line) && !line.empty()) {
    interpret(line);

    std::cout << "> ";
  }
}

void Interpreter::interpret(const std::string& source){

  std::vector<Token> tokens = scan(source); 

  for (Token token: tokens){
    std::cout << token.toString() << std::endl;
  }
}


