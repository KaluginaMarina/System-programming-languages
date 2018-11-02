#ifndef LAB5_PICTURE_H
#define LAB5_PICTURE_H

#include <stdint.h>

typedef struct __attribute__((packed)){
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} bmp_header_t;

typedef struct {
    unsigned char b,g,r;
} pixel_t;

typedef struct {
    uint32_t width, height;
    pixel_t* data;
} image_t;

image_t* rotate(image_t* image);

#endif //LAB5_PICTURE_H
