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
    return 0;
}