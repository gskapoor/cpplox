#include <iostream>
#include <fstream>
#include <string>

#include<Scanner.h>

void report(int line, std::string where, std::string message) {

  std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;

}

void error(int line, std::string message){
  report(line, "", message);
}

void run(std::string source){
  Scanner scanner(source);
  std::vector<Token> tokens = scanner.scanTokens();

  for (Token token: tokens){
    std::cout << token.toString() << std::endl;
  }
}

void runFile(std::string path) {

  std::ifstream inputFile(path);

  if (!inputFile.is_open()){
    std::cerr << "Error opening file: " << path << std::endl;
    return;
  }

  std::string fileContent(
    (std::istreambuf_iterator<char>(inputFile)),
    (std::istreambuf_iterator<char>())
  );

  inputFile.close();

  std::cout << "File Content" << std::endl;
  run(fileContent);

  return;
}

void runPrompt() {
  std::cout << ">> ";

  std::string line;

  while (std::getline(std::cin, line) && !line.empty()) {
    run(line);
    
    std::cout << ">> ";
  }
}

int main(int argc, char* argv[]) {

  if (argc > 2){
    std::cerr << "Usage: " << argv[0] << " <script> " << std::endl;
    return 64;
  } else if (argc == 2){
    runFile(argv[1]);
  } else {
    runPrompt();
  }

  return 0;
}
