#include "Image.h"

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

Image::Image(const char* filename, int flags) {
  if(read(filename, flags)) {
    printf("Read %s\n", filename);
  } else {
    printf("Failed to read %s\n", filename);
  }
}
Image::~Image() {
  image.release();
}

bool Image::read(const char* filename, int flags) {
  image = cv::imread(filename, flags);
  if (!image.data) {
    return 0;
  };
  return 1;
}

bool Image::write(const char* filename) {
  printf("Writing image to %s\n", filename);
  bool success = cv::imwrite(filename, image);

  return success != 0;
}

void Image::show() {
  namedWindow("Display Image", WINDOW_AUTOSIZE);
  cv::imshow("Display Image", image);
  cv::waitKey(0);
}

Image& Image::get_average() {
  average = cv::mean(image);
  return *this;
}

Image& Image::resize(int width, int height) {
  printf("Original height and width: %ix%i\n", image.rows, image.cols);
  Mat resized;

  cv::resize(image, resized, Size(width, height), INTER_LINEAR);
  image = resized;
  printf("New height and width: %ix%i\n", image.rows, image.cols);
  return *this;
}
