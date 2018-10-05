#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "lab3.h"

const int x[] = { 1, 2, 3, 4, 5 };
const int y[] = { 5, 4, 3, 2, 1 };

int main() {
    int sz;
	int n;
	setlocale(LC_CTYPE, "Rus");
	sz = sizeof( x ) / sizeof( x[0] );
	printf("x = ");
	print_array(x, sz);
	printf("y = ");
	print_array(y, sz);
	printf( "Скалярное произведение: %d\n\n", scalar( x, y,  sz));

	printf("Введите число для проверки на простоту: "); 
	scanf("%d", &n);	
	prime_int(n) ? printf("Не является простым\n") : printf("Простое\n");
	return 0;
}