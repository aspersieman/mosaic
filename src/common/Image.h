#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;

enum ImageType {
  PNG, JPG, BMP, TGA
};

struct Image {
  Mat image;
  cv::Scalar average;
  size_t size = 0;

  Image(const char* filename, int flags = 1);
  ~Image();

  bool read(const char* filename, int flags = 1);
  bool write(const char* filename);

  void show();
  Image& get_average();
  Image& resize(int width, int height);
};
