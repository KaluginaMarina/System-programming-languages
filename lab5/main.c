#include <stdio.h>
#include <stdlib.h>
#include "picture.h"


int main() {
    image_t* input_image  = read_bmp("1_1.bmp");
    image_t* output_image = rotate(input_image);
    write_bmp("out.bmp", output_image);
    printf("Я записаль");
    return 0;
}