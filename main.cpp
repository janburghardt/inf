#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include "nonlin.h"
double sieczna(double x0, double x1, double(*fun)(double), double eps, int* n_iter)
{
    double tmp;
    *n_iter = 0;
    while (fabs(fun(x1)) > eps && fabs(x1 - x0) > eps)
    {
        tmp = x1 - fun(x1) * (x1 - x0) / (fun(x1) - fun(x0));
        x0 = x1;
        x1 = tmp;
        (*n_iter)++;
    }
    return x1;
}
double styczna(double x0, double(*fun)(double), double(*poch)(double), double eps, int* n_iter)
{
    double deltaX = 1;
    *n_iter = 0;
    while (fabs(fun(x0)) > eps && fabs(deltaX) > eps)
    {
        deltaX = -fun(x0) / poch(x0);
        x0 = x0 + deltaX;
        (*n_iter)++;
    }
    return x0;
}
double fun(double x)
{
   return  cos(x)-x;
}
double prim(double x)
{
    return -sin(x) - 1;
}
int main()
{
    int inter[18];
    int inters[18];
    double bis;
    double stycz;
    int n = 0;
    double a=-2.0, b=5.0,eps,x;
    while (fun(a) * fun(b) < 0 && n==0)
    {
        for (int i = -20; i < -2; ++i)
        {
            eps = pow(2., i);
            stycz = styczna(a, fun, prim, eps, &inters[i+20]);
            bis=bisec(a, b, fun, eps, &inter[i + 20]);
            printf("%lf  iteracje=%d\n", stycz, inters[i + 20]);
        }
        n++;
    }
    return 0;
}
