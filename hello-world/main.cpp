
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

int main (const int argc, const char *argv[]) {
  int ret = 0;
  std::string path;

  std::cout << "argc = " << argc << std::endl;
  if (argc > 1) {
    path = argv[1];
  } else {
    path = samples::findFile("image.jpeg");
  }
  std::cout << "path = " << path << "." << std::endl;
  Mat img = imread(path, IMREAD_COLOR);

  if (!img.empty()) {
    imshow(path, img);
    int key = waitKey(3*1000);
    if (key == 's')
      imwrite("image.png", img);
  } else {
    std::cout << "ERROR: Failed to read image: " << path << std::endl;
    ret = 1;
  }
  return ret;
}




