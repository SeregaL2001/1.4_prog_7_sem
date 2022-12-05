#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h> // установка бибилиотеки языков для VScode 

#define TEST 5
#define EPS 1e-10


double solution(double x, int a); // мое подобранное решение под краевые условия 

double g(double x, int a); // действие диф оператора на solution

double f(double x, int a, double u_1, double u_2, double u_3, int num); // правая часть для решения Р-К 

void runge_kutta(double *X, int a, double *Res, double u_0, double du_0, double ddu_0, int N); // метод Р-К см вики 

double find_ddu_0(double *X, int a, double u_0, double u_1, double du_0, int N); // поиск краевого условия методом стрельбы 
