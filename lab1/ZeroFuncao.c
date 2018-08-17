#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

double bisseccao (Polinomio p, double a, double b, double eps,
	       int *it, double *raiz) {
  double xnp, xn;
  do {
    xn = (a + b) / 2;
    double *fa, *fxn;
    calcPolinomio_rapido(p, a, fa, NULL);
    calcPolinomio_rapido(p, xn, fxn, NULL);
    if (*fa * *fxn > 0) a = xn;
    else b = xn;
    xnp = (a + b) / 2;
  } while(fabs((xnp - xn) / xnp) > eps);
  *raiz = xnp;
  return 0;
}


double newtonRaphson (Polinomio p, double x0, double eps,
		   int *it, double *raiz) {
  int k = 1;
  double x, erro;
  double *fx0, *dfx0;
  calcPolinomio_rapido(p,x0,fx0,dfx0);
  x = x0 - *fx0 / *dfx0;
  while (fabs((x - x0) / x) > eps && k > *it) {
    x0 = x;
    k++;
    calcPolinomio_rapido(p,x0,fx0,dfx0);
    x = x0 - *fx0 / *dfx0;
  }
  *raiz = x;
  if (k > *it) return -1;
  return 0;
}


double secante (Polinomio p, double x0, double x1, double eps,
	     int *it, double *raiz) {

}


void calcPolinomio_rapido(Polinomio p, double x, double *px, double *dpx) {
  double b = p.p[p.grau];
  printf("b = %lf\n", b);
  double c = b;
  int k;
  for (int k = p.grau - 1; k; --k) {
    b = p.p[k] + (b * x);
    printf("b = %lf + (%lf * %lf) = %lf\n", p.p[k], c, x, b);
    c = b + c * x;
  }
  b = p.p[0] + (b * x);
  *px = b;
  *dpx = c;
}


void calcPolinomio_lento(Polinomio p, double x, double *px, double *dpx) {
  double result = 0;
  double ant = 0;
  for(int i = 0; i <= p.grau; i++) {
    ant = result;
    double power = pow(x,p.grau-i);
    result = result + p.p[i] * power;
    printf("b = %lf + (%lf * %lf) = %lf\n", ant, p.p[i], power, result);
  }
  *px = result;
}
