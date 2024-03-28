
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

int main (const int argc, const char *argv[]) {
  int ret = 0;
  Mat A, C;

  if (argc > 1) {
    A = imread(argv[1], IMREAD_COLOR);
    Mat B(A);
    C = A;

    imshow("shitty title", A);
    imshow("another shitty title", B);
    imshow("yet another even shittier title", C);
    waitKey(0);
  } else {
    std::cout << "ERROR: Failed to read image " << argv[1] << std::endl;
    ret = 1;
  }

  return ret;
}




