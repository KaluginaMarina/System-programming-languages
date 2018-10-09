#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "lab3.h"


int main() {
	size_t sz;
	long unsigned int n;
	size_t i;
	int *x;
	int *y;
	
	printf("Введите длинну вектора: ");
	scanf("%lu", &sz);
	
	x =  (int*)malloc(sz * sizeof(int));
	y =  (int*)malloc(sz * sizeof(int));
	
	printf ("\nВведите первый вектор: ");
	for (i = 0; i < sz; ++i) {
		scanf("%d", (x+i));
	}
	printf ("\nВведите второй вектор: ");
	for (i = 0; i < sz; ++i) {
		scanf("%d", (y+i));
	}
	
	setlocale(LC_CTYPE, "Rus");
	printf("x = ");
	print_array(x, sz);
	printf("y = ");
	print_array(y, sz);
	printf( "Скалярное произведение: %d\n\n", scalar( x, y,  sz));

	printf("Введите число для проверки на простоту: "); 
	if (scanf("%lu", &n)) {	
		prime_int(n) ? printf("%lu не является простым\n", n) : printf("%lu - простое\n", n);
	} else {
		printf("Было введено не число.\n");
	}
	return 0;
}