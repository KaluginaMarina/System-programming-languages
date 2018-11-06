#include <stdio.h>
#include <stdlib.h>
#include "picture.h"
#include "memory_mapping_and_friends.h"


int main() {

    rotate_bmp("11sm-1.bmp", "out.bmp");
    image_bmp_fused_rotate_90cw("11sm-1.bmp", "out2.bmp");
    return 0;
    image_t* input_image = (image_t*)malloc(sizeof(image_t));
    switch (read_bmp("11sm.bmp", input_image)) {
        case READ_FILENAME_NOT_FOUND :{
            printf("Не найден файл.\n");
            break;
        }
        case READ_INVALID_BITS: {
            printf("Проблемы с данными.\n");
            break;
        }
        case READ_INVALID_HEADER: {
            printf("Проблемы с заголовком.\n");
            break;
        }
        case READ_OK:{
            printf("Изображение получено.\n");
            break;
        }
        default: {
            printf("Вообще что-то не так.\n");
            break;
        }
    }

    image_t* output_image = rotate(input_image);
    switch (write_bmp("out.bmp", output_image)){
        case WRITE_IMAGE_NOT_FOUND: {
            printf("Изображение для записи не найдено.\n");
            break;
        }
        case WRITE_FILENAME_NOT_FOUND: {
            printf("А тут как-то неправильно передается filename.\n");
            break;
        }
        case WRITE_ERROR: {
            printf("Незнаю, как такое получилось, но тут ошибка при открытии файла.\n");
            break;
        }
        case WRITE_OK: {
            printf("Я записаль:3\n");
            break;
        }
        default: {
            printf("Совсем что-то не так пошло.\n");
            break;
        }
    }
    return 0;
}