/**
 * @Author: serega
 * @Date:   2022-12-02T13:05:31+03:00
 * @Last modified by:   serega
 * @Last modified time: 2022-12-02T13:08:14+03:00
 */


#include "method.hpp"


int main()
{
    setlocale(LC_ALL, "Rus");

    int N = 1; // число точек 
    int a; // параметр альфа = 1 или 10 
    double h; // шаг сетки 
    int k; // параметр для уменьшения шага h 
    double *X; // массив точек, длины n 
    double *U; // массив значений функции U в точке x_i, длины n  
    double error[TEST];

    printf("Введите число точек: ");
    scanf("%d", &N);
    printf("Введите параметр а: ");
    scanf("%d", &a);

    double u_0 = 0, u_1 = a, du_0 = 0, ddu_0 = 0; // краевые значения 

    printf("Исходная задача имеет следующий вид:\n");
    printf("u + u' * cos(x) + u''' = g(x)\n");
    printf("u(0) = u'(0) = 0\n");
    printf("u(1) = %d \n", a);
    h = 1.0/(N-1);

     X = (double *)malloc(N* sizeof(double));
     U = (double *)malloc(N* sizeof(double));
     
    X[0] = 0; 
    for(int i = 1; i < N; i++)
    {
        X[i] = X[i - 1] + h;
    }

    ddu_0 = find_ddu_0(X, a, u_0, u_1, du_0, N);
    runge_kutta(X, a, U, u_0, du_0, ddu_0, N);

    free(X);
    free(U);
    return 0;
}
