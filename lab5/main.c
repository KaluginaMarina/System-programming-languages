#include <stdio.h>
#include <stdlib.h>
#include "picture.h"


int main() {
    image_t* input_image  = read_bmp("Lights.bmp");
    image_t* output_image = rotate(input_image);
    write_bmp("out.bmp", output_image, &header);
    printf("Я записаль");
    return 0;
}