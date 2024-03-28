#include <iostream>
#include <fstream>

using namespace std;

const unsigned int width = 1920, height = 1080;

int main () {
  
  ofstream image;
  image.open("image.ppm");
  
  if (image.is_open()) {
    
    // Header info
    image << "P3" << endl;
    image << width << " " << height << endl;
    image << "255" << endl;

    int shade = 40;

    for (int i=0; i<width; i++) {
      for (int j=0; j<height; j++)
	image << shade << " " << shade << " " << 0 << endl;
    }
  }
  image.close();
}
