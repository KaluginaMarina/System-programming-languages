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
    fwrite(image->data, 1, new_image->height * new_image->width * sizeof(pixel_t), output);
    fclose(output);
}

image_t* read_bmp(char const* filename){
    FILE *input = fopen(filename, "rb");
    fread(&header, 1, sizeof(header), input);

    uint8_t * data = (uint8_t *)malloc(header.biSizeImage);
    fseek(input, header.bOffBits, SEEK_SET);
    fread(data, 1, header.biSizeImage, input);

    image_t* input_image = (image_t*)malloc(sizeof(image_t));
    input_image->data = (pixel_t*)malloc(header.biHeight * header.biWidth * sizeof(pixel_t));

    int padding = header.biWidth % 4;
    for (uint32_t i = 0; i < header.biHeight; ++i){
        for (uint32_t j = 0; j < header.biWidth; ++j){
            uint64_t offset = sizeof(pixel_t)*(i*header.biWidth + j) + padding*i;
            *(input_image->data + i*header.biWidth + j) = *(pixel_t*)(((uint8_t*)data) + offset);
        }
    }
    input_image->height = header.biHeight;
    input_image->width = header.biWidth;
    fclose(input);
    return input_image;
}