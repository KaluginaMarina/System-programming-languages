#include <stdlib.h>
#include "picture.h"

image_t* rotate(image_t* image){
    image_t* new_image = (image_t*)malloc(sizeof(image_t));
    new_image->data = (pixel_t*)malloc(image->height*image->width* sizeof(pixel_t));
    new_image->width = image->height;
    new_image->height = image->width;

    uint32_t i, j;
    for (i = 0; i < image->height; ++i){
        for (j = 0; j < image->width; ++j){
            *(new_image->data + j*image->height + i) = *(image->data + i*image->width + j);
        }
    }
    return new_image;
}