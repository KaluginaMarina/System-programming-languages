#include <stdio.h>
#include "allocation.h"

int main() {
    init(100);
    int* a = (int*)_malloc(sizeof(int)*300);
    for (int i = 0; i < 300; ++i){
        a[i] = 0;
    }

    for (int i = 0; i < 300; i+=30){
        printf("%d\n", a[i]);
    }

    _free(a);

    int* b = (int*)_malloc(sizeof(int)*3);
    for (int i = 0; i < 3; ++i){
        b[i] = 1;
    }

    for(int i = 0; i < 3; ++i){
        printf("%d\n", b[i]);
    }
    return 0;
}