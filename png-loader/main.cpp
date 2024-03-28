
#include <iostream>
#include <fstream>

int main () {
  
  const char *filename = "orange.png";
  
  std::fstream filestream;
  filestream.open(filename, std::fstream::in | std::fstream::binary);

  std::filebuf* read_buffer = filestream.rdbuf();
  char c = read_buffer->sbumpc();
  while (c != EOF) {
    std::cout << c;
    c = read_buffer->sbumpc();
  }
  
  filestream.close();
  
  return 0;
}
