#include "bmp.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "image_server.h"

// calculate the number of bytes of memory needed to serialize the bitmap
// that is, to write a valid bmp file to memory
size_t bmp_calculate_size(bitmap_t *bmp) {
  size_t size_FH = sizeof(BITMAPFILEHEADER);
  size_t size_IH = sizeof(BITMAPINFOHEADER);
  size_t size_img = bmp->width * bmp->height * sizeof(color_bgr_t);
  return (size_FH + size_IH + size_img);
}

// write the bmp file to memory at data, which must be at least
// bmp_calculate_size large.
void bmp_serialize(bitmap_t *bmp, uint8_t *data) {
  BITMAPFILEHEADER file_header = { 0 }; // start out as all zero values
  file_header.F_bfType = 'B';
  file_header.L_bfType = 'M';
  file_header.bfSize = bmp_calculate_size(bmp);
  file_header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  BITMAPINFOHEADER info_header = { 0 };
  info_header.biSize = sizeof(BITMAPINFOHEADER);
  info_header.biWidth = bmp->width;
  info_header.biHeight = bmp->height;
  info_header.biPlanes = 1;
  info_header.biBitCount = 24;
  info_header.biCompression = 0;
  info_header.biSizeImage = 0;
  info_header.biXPelsPerMeter = 2835;
  info_header.biYPelsPerMeter = 2835;

  uint8_t *data_out = data;
  memcpy(data_out, &file_header, sizeof(file_header));
  data_out += sizeof(file_header);
  memcpy(data_out, &info_header, sizeof(info_header));
  data_out += sizeof(info_header);
  for (int i = bmp->height - 1; i >= 0; i--) {
    memcpy(data_out, &bmp->data[bmp->width * i], bmp->width * sizeof(color_bgr_t));
    data_out += bmp->width * sizeof(color_bgr_t);
  }
}

int main (void) {
  bitmap_t bmp = { 0 }; // initialize to zeros
  bmp.width = 640;
  bmp.height = 480;
  // color_bgr_t represents the color for each pixel
  // calloc gives enough space for width*height of these pixels
  // and calloc also sets the initial values of all of these to zero (black)
  bmp.data = calloc(bmp.width * bmp.height, sizeof(color_bgr_t));
  
  size_t bmp_size = bmp_calculate_size(&bmp);
  uint8_t *serialized_bmp = malloc(bmp_size);
  bmp_serialize(&bmp, serialized_bmp);
  // serialized_bmp now has the full bmp formatted image

  // write to a file so we can check if it is a valid image
  FILE *f = fopen("my_image.bmp", "wb");
  fwrite(serialized_bmp, bmp_size, 1, f);
  fclose(f);
  image_server_set_data(bmp_size, serialized_bmp);
  image_server_start("8000"); // you could change the port number, but animation.html wants 8000
  sleep(1);
  // remember to later free the bmp.data when we are done using it
  free(bmp.data);
  free(serialized_bmp);
  return 0;
}
