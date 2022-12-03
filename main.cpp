/**
 * @Author: serega
 * @Date:   2022-12-02T13:05:31+03:00
 * @Last modified by:   serega
 * @Last modified time: 2022-12-02T13:08:14+03:00
 */



#include "method.h"

int main()
{
    setlocale(LC_ALL, "Rus");

    int N = 1; // число точек 
    int a; // параметр альфа = 1 или 10 
    double h; // шаг сетки 
    double *X; // массив точек, длины n 
    double *Y; // массив значений функции U в точке x_i, длины n  

    printf("Введите число точек: ");
    scanf("%d", &N);
    printf("Введите параметр а: ");
    scanf("%d", &a);

    h = 1.0/(N-1);

    X = (double *)malloc(N* sizeof(double));
    Y = (double *)malloc(N* sizeof(double));

    return 0;
}
