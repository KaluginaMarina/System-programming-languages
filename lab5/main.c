#include <stdio.h>
#include <stdlib.h>
#include "picture.h"

int main() {
    bmp_header_t pict;
    FILE *input = fopen("11sm.bmp", "rb");
    fread(&pict, 1, sizeof(pict), input);

    pixel_t* data = (pixel_t*)malloc(pict.biSizeImage);
    fseek(input, pict.bOffBits, SEEK_SET);
    fread(data, 1, pict.biSizeImage, input);

    image_t* input_image = (image_t*)malloc(sizeof(image_t));

    input_image->data = data;
    input_image->height = pict.biHeight;
    input_image->width = pict.biWidth;


    image_t* output_image = rotate(input_image);

    write_bmp("out.bmp", output_image, &pict);

    fclose(input);

    printf("Я записаль");
    return 0;
}