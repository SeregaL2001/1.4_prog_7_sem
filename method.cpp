#include "method.hpp"



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
        return u_2;
        // u'_1 = u_2
        break;

        case 1:
        return u_3;
        // u'_2 = u_3
        break;

        case 2:
        return g(x, a) - cos(x) * u_2 - u_1; 
        // u'_3 = g(x, a) - cos(x) * u_2 - u_1; 
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

    double **Y;
    Y = (double **)malloc(N * sizeof(double *)); 

    for (int i = 0; i < N; i++) 
    {
        Y[i] = (double *)malloc(3 * sizeof(double));
    }

    
    // y(x_0) = y_0
    Y[0][0] = u_0;
    Y[0][1] = du_0;
    Y[0][2] = ddu_0;

    for (int i = 0; i < N - 1; i++) // отвечает за строку, т е за iую точку 
    {
        for (int j = 0; j < 3; j++) // отвечает за столбец, т е за jое уравнение Коши
        {
            k_1[j] = f(X[i], a, Y[i][0], Y[i][1], Y[i][2], j);
            // k_1 = F(x_n, y_n)
        }
        for (int j = 0; j < 3; j++)  
        {
            k_2[j] = f(X[i] + (h / 2), a, Y[i][0] + (h / 2) * k_1[0], Y[i][1] + (h / 2) * k_1[1], Y[i][2] + (h / 2) * k_1[2], j);
            // k_2 = F(x_n + h/2, y_n + h/2 * k_1)
        }
        for (int j = 0; j < 3; j++) 
        {
            k_3[j] = f(X[i] + (h / 2), a, Y[i][0] + (h / 2) * k_2[0], Y[i][1] + (h / 2) * k_2[1], Y[i][2] + (h / 2) * k_2[2], j);
            // k_3 = F(x_n + h/2, y_n + h/2 * k_2)
        }
        for (int j = 0; j < 3; j++) 
        {
            k_4[j] = f(X[i] + h, a, Y[i][0] + h * k_3[0], Y[i][1] + h * k_3[1], Y[i][2] + h * k_3[2], j);
            // k_4 = F(x_n + h, y_n +h * k_3)
        }
        for (int j = 0; j < 3; j++) 
        {
            Y[i + 1][j] = Y[i][j] + (h / 6) * (k_1[j] + 2 * k_2[j] + 2 * k_3[j] + k_4[j]);
            // Y_(n+1) = Y_(n) + h/6 * (k_1 + 2 * k_2 + 2 * k_3 + k_4)
        }
    }
    for (int i = 0; i < N; i++)
    {
        Res_u[i] = Y[i][0];
        free(Y[i]);
    }
    free(Y); // ? 

}

double find_ddu_0(double *X, int a, double u_0, double u_1, double du_0, int N)
{
    double f_cent, f_right;
    double right_diff;
    double result = 0;
    double *C;

    C = (double *)malloc(N * sizeof(double));
    
    runge_kutta(X, a, C, u_0, du_0, result, N); // ?
    
    f_cent = C[N - 1];

    runge_kutta(X, a, C, u_0, du_0, result + 1, N);

    f_right = C[N - 1];
    right_diff = (f_right - f_cent);
    result = result + (u_1 - f_cent) / right_diff;  

    free(C);
    return result;
}
