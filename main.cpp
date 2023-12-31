#include <iostream>
#include <fstream>
#include <string>

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

  std::cout << "File Content\n" << fileContent << std::endl;

  return;
}

void runPrompt() {
  std::cout << ">> ";

  std::string line;

  while (std::getline(std::cin, line) && !line.empty()) {
    std::cout << line << std::endl;
    
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
