#include <stdint.h>
#include <cstdio>
#include <complex>
#include <string.h>

//legacy feature of C
#undef __STRICT_ANSI__

enum ImageType {
  PNG, JPG, BMP, TGA
};

struct Thumbnail {
  uint8_t* data = NULL;
  size_t size = 0;
  int w;
  int h;
  int channels;

  Thumbnail(const char* filename, int channel_force = 0);
  Thumbnail(int w, int h, int channels = 3);
  Thumbnail(const Thumbnail& img);
  ~Thumbnail();
};
