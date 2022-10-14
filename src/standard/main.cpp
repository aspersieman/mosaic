#include <filesystem>
#include <iostream>
#include <sys/stat.h>
#include <vector>

#include "../common/Image.h"

using namespace std;

bool setup(const char* outputDirectory)
{
  // check if output directory has been created
  int check;
  check = mkdir(outputDirectory, 0777);
  if (!check) {
    printf("Output directory created\n");
  }
  return 1;
}

bool thumbnails(const char* imagesDirectory, const char* outputDirectory, int width, int height)
{
  using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
  std::vector<Image> images;
  for (const auto& dirEntry : recursive_directory_iterator(imagesDirectory)) {
    if (!dirEntry.is_regular_file()) {
      continue;
    }
    std::filesystem::path file = dirEntry.path();
    // TODO add support for all filetypes
    if (file.extension() != ".jpg") {
      continue;
    }

    char* fileName;
    fileName = (char*)calloc(strlen(dirEntry.path().string().c_str()) + strlen(file.filename().string().c_str()) + 1, sizeof(char));
    strcpy(fileName, file.filename().string().c_str());

    char* imageSource;
    imageSource = (char*)calloc(strlen(imagesDirectory) + strlen(fileName) + 1, sizeof(char));
    strcpy(imageSource, imagesDirectory);
    strcat(imageSource, fileName);
    Image image(imageSource);
    image.resize(width, height);

    char* imageTarget;
    imageTarget = (char*)calloc(strlen(outputDirectory) + strlen(file.filename().string().c_str()) + 1, sizeof(char));
    strcpy(imageTarget, outputDirectory);
    strcat(imageTarget, file.filename().string().c_str());
    image.write(imageTarget);
    image.get_average();
    images.push_back(image);
    image.show();
    printf("Filename: %s; average bgr: %g,%g,%g\n", imageSource, image.average[0], image.average[1], image.average[2]);
    std::cout << "\n";
  }
  return 1;
}

int main(int argc, char** argv)
{
  // TODO allow cleaning of all output/temp files

  // TODO accept as input arguments
  const char* imagesDirectory = "/home/nicol/Downloads/motleymaker/test/";
  const char* outputDirectory = "output/";
  const int width = 300;
  const int height = 300;

  setup(outputDirectory);
  thumbnails(imagesDirectory, outputDirectory, width, height);

  return 0;
}
