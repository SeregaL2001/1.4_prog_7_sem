

#include "method.hpp"


int main()
{
    setlocale(LC_ALL, "Rus");

    int N = 20; // число точек 
    int a; // параметр альфа = 1 или 10 
    double h; // шаг сетки 
    int k = 2; // параметр для уменьшения шага h 
    double *X; // массив точек, длины n 
    double *U; // массив значений функции U в точке x_i, длины n  
    double error[TEST];
    double demo;

    printf("Введите число точек: ");
    scanf("%d", &N);
    printf("Введите параметр а: ");
    scanf("%d", &a);

    double u_0 = 0, u_1 = a, du_0 = 0; // краевые значения 
    double ddu_0; // неизвестное краевое 

    printf("Исходная задача имеет следующий вид:\n");
    printf("u + u' * cos(x) + u''' = g(x)\n");
    printf("u(0) = u'(0) = 0\n");
    printf("u(1) = %d \n", a);

    for(int j = 0; j < TEST; j++)
 {
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
    
    FILE *file;
        switch(j)
        {
            case 0:
                file = fopen("test_1.txt", "w");
                break;
            case 1:
                file = fopen("test_2.txt", "w");
                break;
            case 2:
                file = fopen("test_3.txt", "w");
                break;
            case 3:
                file = fopen("test_4.txt", "w");
                break;
            case 4:
                file = fopen("test_5.txt", "w");
                break;
            case 5:
                file = fopen("test_6.txt", "w");
        }

     error[j] = 0;
     for(int i = 0; i < N; i++)
     {
        // ||error[j]|| = max|error[j]|, j = 0, 1,......, N-1
        if(error[j] < fabs(U[i] - solution(X[i], a)))
        {
             error[j] = fabs(U[i] - solution(X[i], a));
        }

        fprintf(file, "%lf %lf\n", X[i], U[i]);
     }

        printf("При h = %.8f:\n error = %le\n", h, error[j]);

        fclose(file);
        free(X);
        free(U);
        N = (N - 1) * k + 1;
 }

    printf("отношение норм погрешностей ||error[j]|| / ||error[j + 1]||:\n");
    for (int j = 0; j < TEST - 1; j++) 
    {
        printf("%.8f\n", error[j] / error[j + 1]);
    }
    return 0;
}
