#include <stdio.h>
#include <stdlib.h>
#include "picture.h"


int main() {
    image_t* input_image = (image_t*)malloc(sizeof(image_t));
    read_bmp("1_1.bmp", input_image);
    image_t* output_image = rotate(input_image);
    write_bmp("out.bmp", output_image);
    printf("Я записаль");
    return 0;
}