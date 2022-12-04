#include "method.h"


double solution(double x, int a)
{
    return (a/sin(1)) * (x * sin(x)); // u == solution 
}

double g(double x, int a)
{
    double res;
    res = (x * cos(x) + sin(x)) * (a/sin(1)); // это по факту u'
    res = cos(x) * res; // u' * cos(x)
    res = res + (a * x * sin(x)) * (1/sin(1)); // u + u' * cos(x)
    res = res + (-a/sin(1)) * (3 * sin(x) + x * cos(x)); // u + u' * cos(x) + u'''
    return res;
}

double f( double x, int a, double u_1, double u_2, double u_3, int num)
{
    switch(num) 
    {
        case 0:
        return u_1;
        break;

        case 1:
        return u_2;
        break;

        case 2:
        return g(x, a) - cos(x) * u_2 - u_1;
        break;
    }
    return 0; 
}

void runge_kutta(double *X, int a, double *Res_u, double u_0, double du_0, double ddu_0, int N)
{
    double k_1[3];
    double k_2[3];
    double k_3[3];
    double k_4[3];

    double h = 1.0 / (N - 1);

    double **U;
    U = (double **)malloc(N * sizeof(double *));

    for (int i = 0; i < N; i++) 
    {
        U[i] = (double *)malloc(3 * sizeof(double));
    }

    U[0][0] = u_0;
    U[0][1] = du_0;
    U[0][2] = ddu_0;

    for (int i = 0; i < N - 1; i++) // отвечает за строку 
    {
        for (int j = 0; j < 3; j++) // отвечает за столбец 
        {
            k_1[j] = f(X[i], a, U[i][0], U[i][1], U[i][2], j);
            // k_1 = f(x_n, y_n)
        }
        for (int j = 0; j < 3; j++)  
        {
            k_2[j] = f(X[i] + (h / 2), a, U[i][0] + (h / 2) * k_1[0], U[i][1] + (h / 2) * k_1[1], U[i][2] + (h / 2) * k_1[2], j);
            // k_2 = f(x_n + h/2, y_n + h/2 * k_1)
        }
        for (int j = 0; j < 3; j++) 
        {
            k_3[j] = f(X[i] + (h / 2), a, U[i][0] + (h / 2) * k_2[0], U[i][1] + (h / 2) * k_2[1], U[i][2] + (h / 2) * k_2[2], j);
            // k_3 = f(x_n + h/2, y_n + h/2 * k_2)
        }
        for (int j = 0; j < 3; j++) 
        {
            k_4[j] = f(X[i] + h, a, U[i][0] + h * k_3[0], U[i][1] + h * k_3[1], U[i][2] + h * k_3[2], j);
            // k_4 = f(x_n + h, y_n +h * k_3)
        }
        for (int j = 0; j < 3; j++) 
        {
            U[i + 1][j] = U[i][j] + (h / 6) * (k_1[j] + 2 * k_2[j] + 2 * k_3[j] + k_4[j]);
            // U_(n+1) = U_(n) + h/6 * (k_1 + 2 * k_2 + 2 * k_3 + k_4)
        }
    }
    for (int i = 0; i < N; i++)
    {
        Res_u[i] = U[i][0];
        free(U[i]);
    }
    free(U); // ? 

}

double find_ddu_0(double *X, int a, double u_0, double u_1, double du_0, int N)
{
    double f_cent, f_right;
    double right_diff;
    double result = 0;
    double *Y;

    Y = (double *)malloc(N * sizeof(double));
    
    runge_kutta(X, a, Y, u_0, du_0, result, N);
    
    f_cent = Y[N - 1];

    runge_kutta(X, a, Y, u_0, du_0, result + 1, N);

    f_right = Y[N - 1];
    right_diff = (f_right - f_cent);
    result += (u_1 - f_cent) / right_diff;  

    free(Y);
    return result;
}