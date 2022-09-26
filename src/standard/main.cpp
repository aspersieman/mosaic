#include <filesystem>
#include <iostream>

#include "../common/Thumbnail.h"

int main(int argc, char** argv) {
  printf("Hello World!\n");
  using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
  const char* myPath = "/home/nicol/src/mosaic/src/";
  for (const auto& dirEntry : recursive_directory_iterator(myPath)) {
     std::cout << dirEntry << std::endl;
  }
  return 0;
}
