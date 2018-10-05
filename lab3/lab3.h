#include <stdio.h>

#ifndef LAB3
#define LAB3

/* Функция считает скалярное произведение 2-х векторов
 * @param const int a[], const int b[] - указатели на начало векторов
 * @param int sz - размер векторов
 * @return размер массива
 */
int scalar( const int a[], const int b[], size_t sz );

/* Функция для записи массива на экаран
*/
int print_array(const int a[], size_t sz);

/* Функция проверки числа на простоту
 * @param x - число:)
 * @return 0 - число х - простое; 1 - число х - составное
 */
int prime_int(int x);
#endif 