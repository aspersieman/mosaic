#define BYTE_BOUND(value) value < 0 ? 0 : (value > 255 ? 255 : value)

#include "Thumbnail.h"

Thumbnail::Thumbnail(const char* filename, int channel_force) {
  printf("Constructor 1\n");
}

Thumbnail::Thumbnail(int w, int h, int channels) : w(w), h(h), channels(channels) {
  size = w * h * channels;
  data = new uint8_t[size];
}

Thumbnail::Thumbnail(const Thumbnail& img) : Thumbnail(img.w, img.h, img.channels) {
  memcpy(data, img.data, size);
}

Thumbnail::~Thumbnail() {
  free(data);
}
