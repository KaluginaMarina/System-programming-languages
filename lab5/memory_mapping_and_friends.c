#include <malloc.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <memory.h>
#include "memory_mapping_and_friends.h"
#include "picture.h"

void rotate_bmp(char* input_filename, char* output_filename){
    FILE* input = fopen(input_filename, "rb");
    FILE* output = fopen(output_filename, "wb");

    bmp_header_t header;
    fread(&header, 1, sizeof(header), input);
    uint8_t* data = (uint8_t *)malloc(header.biSizeImage);
    fseek(input, header.bOffBits, SEEK_SET);
    fread(data, sizeof(pixel_t), header.biSizeImage, input);

    int input_padding = header.biWidth % 4;
    int output_padding = header.biHeight % 4;
    uint32_t tmp = header.biWidth;
    header.biWidth = header.biHeight;
    header.biHeight = tmp;
    header.biSizeImage = sizeof(pixel_t) * header.biHeight * (header.biWidth) + output_padding*header.biHeight;
    header.bfileSize = header.biSizeImage + sizeof(header);

    fwrite(&header, 1, sizeof(bmp_header_t), output);

    header.biHeight = header.biWidth;
    header.biWidth = tmp;

    fseek(input, sizeof(bmp_header_t), SEEK_SET);
    for (long int i = 0; i < header.biHeight; ++i){
        for (long int j = 0; j < header.biWidth; ++j) {
            pixel_t pixel;
            fread(&pixel, 1, sizeof(pixel_t), input);

            if (j == header.biWidth - 1){
                fseek(input, input_padding, SEEK_CUR);
            }
            fseek(output, sizeof(bmp_header_t) + sizeof(pixel_t)*((header.biWidth - 1 - j)*header.biHeight + i) + (header.biWidth - 1 - j)*output_padding, SEEK_SET);

            fwrite(&pixel, 1, sizeof(pixel_t), output);
            fflush(output);
        }
    }

    fclose(input);
    fclose(output);
}




int compute_total_padding_rotated(bmp_header_t* header) {
    return header->biWidth * (header->biHeight % 4);
}

void rotate_right_padded(const uint8_t* src, uint8_t* dst, uint32_t width, uint32_t height) {
    for (uint32_t h = 0; h < height; h++) {
        uint64_t src_padding = h * (width % 4);

        for (uint32_t w = 0; w < width; w++) {
            uint64_t dst_padding = (width - w) * (height % 4);

            *(pixel_t*)(dst + (((width - 1 - w) * height) + h) * sizeof(pixel_t) + dst_padding) =
                    *(pixel_t*)(src + (h * width + w) * sizeof(pixel_t) + src_padding);
        }
    }
}

void image_bmp_fused_rotate_90cw(const char* src_path, const char* dst_path) {
    struct stat src_stat;
    int src_fd = open(src_path, O_RDONLY);
    int dst_fd = open(dst_path, O_RDWR | O_CREAT | O_TRUNC, (mode_t) 0644);

    fstat(src_fd, &src_stat);
    size_t src_size = src_stat.st_size;

    uint8_t* src = mmap(NULL, src_size, PROT_READ, MAP_SHARED, src_fd, 0);
    bmp_header_t header = *((bmp_header_t*) src);

    uint32_t width = header.biWidth;
    uint32_t height = header.biHeight;
    size_t dst_size = header.bOffBits +
                      width * height * sizeof(pixel_t) + compute_total_padding_rotated(&header);

    /* "Stretch" the destination to its full size */
    lseek(dst_fd, dst_size - 1, SEEK_SET);
    write(dst_fd, "", 1);

    uint8_t* dst = mmap(NULL, dst_size, PROT_READ | PROT_WRITE, MAP_SHARED, dst_fd, 0);

    rotate_right_padded(src + header.bOffBits, dst + header.bOffBits, width, height);

    header.biHeight = width;
    header.biWidth = height;
    memcpy(dst, &header, sizeof(bmp_header_t));

    msync(dst, dst_size, MS_SYNC);
    munmap(src, src_size);
    munmap(dst, src_size);

    close(src_fd);
    close(dst_fd);
}