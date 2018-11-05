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

typedef enum {
    READ_OK = 0,
    READ_FILE_NOT_FOUND,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
} read_error_code_t;



/**
 * Функция переворота картинки
 * @param image - изображение типа image_t
 * @return перевернутое изображение
 */
image_t* rotate(image_t const* image);

/**
 * Функция чтения байт с bmp-файла
 * @param filename - имя bmp-файла
 * @param new_image - для записи прочитанной картинки
 * @return   read_error_code_t
 */
read_error_code_t read_bmp(char const* filename, image_t* new_image);

void write_bmp(char const* filename, image_t const* image);

#endif //LAB5_PICTURE_H
