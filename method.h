#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h> // установка бибилиотеки языков для VScode 

#define EPS 1e-10

double solution(double x, double a); // мое подобранное решение под краевые условия 

double g(double x, double a);

void runge_kutta(double *X, double *Res, double y_0, double dy_0, double ddy_0, int N);

double find_ddu_0(double *X, double y_0, double y_1, double dy_0, int N); 