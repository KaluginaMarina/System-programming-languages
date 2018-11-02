#include <stdlib.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include "picture.h"

image_t* rotate(image_t const* image){
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

void write_bmp(char const* filename, image_t const* image, bmp_header_t* header){
    int padding = image->width % 4;
    uint32_t i, j;
    image_t* new_image = (image_t*)malloc(sizeof(image_t));
    new_image->width = image->width+padding;
    new_image->height = image->height;
    new_image->data = (pixel_t*)calloc(1, new_image->height * new_image->width * sizeof(pixel_t));

    for (i = 0; i < new_image->height; ++i){
        for (j = 0; j < new_image->width; ++j){
            if(j < new_image->width - padding) {
                *(new_image->data + i * new_image->width + j) = *(image->data + i * image->width + j);
            }
        }
    }

    FILE* output = fopen(filename, "wb+");
    header->biWidth = new_image->width - padding;
    header->biHeight = new_image->height;

    fwrite(header, 1, sizeof(bmp_header_t), output);
    fwrite(image->data, 1, image->height * image->width * sizeof(pixel_t), output);
    fclose(output);
}

image_t* read_bmp(char const* filename){

}

/*
 *             *(new_image->data + i*image->width + j) =
                    (j >= image->width - padding) ? pixel : *(image->data + i*image->width + j);
 */