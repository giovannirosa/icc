#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

int bisseccao (Polinomio p, double a, double b, double *eps,
	       int *it, double *raiz, int rapido) {
  double xnp, xn;
  double *fa = (double*) malloc(sizeof(double));
  double *fxn = (double*) malloc(sizeof(double));
  *it = 0;
  do {
    if (*it > MAXIT) return -1;
    *it = *it + 1;
    xn = (a + b) / 2;
    if (rapido == 1) {
      calcPolinomio_rapido(p, a, fa, NULL);
      calcPolinomio_rapido(p, xn, fxn, NULL);
    } else {
      calcPolinomio_lento(p, a, fa, NULL);
      calcPolinomio_lento(p, xn, fxn, NULL);
    }
    if (*fa * *fxn > 0) a = xn;
    else b = xn;
    xnp = (a + b) / 2;
    *eps = fabs((xnp - xn) / xnp);
    // printf("Tentativa %d, xnp = %lf, absx = %lf\n", *it, xnp, *eps);
  } while(*eps > EPS);
  *raiz = xnp;
  return 0;
}


int newtonRaphson (Polinomio p, double x0, double *eps,
		   int *it, double *raiz, int rapido) {
  *it = 1;
  double x, erro;
  double *fx0 = (double*) malloc(sizeof(double));
  double *dfx0 = (double*) malloc(sizeof(double));
  if (rapido == 1) {
    calcPolinomio_rapido(p,x0,fx0,dfx0);
  } else {
    calcPolinomio_lento(p,x0,fx0,dfx0);
  }
  x = x0 - (*fx0 / *dfx0);
  *eps = fabs((x - x0) / x);
  // printf("Tentativa %d, x = %lf, absx = %lf\n", *it, x, *eps);
  while (*eps > EPS && *it < MAXIT) {
    *it = *it + 1;
    x0 = x;
    if (rapido == 1) {
      calcPolinomio_rapido(p,x0,fx0,dfx0);
    } else {
      calcPolinomio_lento(p,x0,fx0,dfx0);
    }
    x = x0 - (*fx0 / *dfx0);
    *eps = fabs((x - x0) / x);
    // printf("Tentativa %d, x = %lf, absx = %lf\n", *it, x, *eps);
  }
  *raiz = x;
  if (*it > MAXIT) return -1;
  return 0;
}


int secante (Polinomio p, double x0, double x1, double *eps,
	     int *it, double *raiz, int rapido) {
  *it = 1;
  double x, erro;
  double *fx0 = (double*) malloc(sizeof(double));
  double *dfx0 = (double*) malloc(sizeof(double));
  double *fx1 = (double*) malloc(sizeof(double));
  double *dfx1 = (double*) malloc(sizeof(double));
  if (rapido == 1) {
    calcPolinomio_rapido(p,x0,fx0,dfx0);
    calcPolinomio_rapido(p,x1,fx1,dfx1);
  } else {
    calcPolinomio_lento(p,x0,fx0,dfx0);
    calcPolinomio_lento(p,x1,fx1,dfx1);
  }
  x = x1 - (*fx1 * (x1 - x0)) / (*dfx1 - *dfx0);
  *eps = fabs((x - x1) / x);
  // printf("Tentativa %d, x = %lf, absx = %lf\n", *it, x, *eps);
  while (*eps > EPS && *it < MAXIT) {
    *it = *it + 1;
    x0 = x1;
    x1 = x;
    if (rapido == 1) {
      calcPolinomio_rapido(p,x0,fx0,dfx0);
      calcPolinomio_rapido(p,x1,fx1,dfx1);
    } else {
      calcPolinomio_lento(p,x0,fx0,dfx0);
      calcPolinomio_lento(p,x1,fx1,dfx1);
    }
    x = x1 - (*fx1 * (x1 - x0)) / (*dfx1 - *dfx0);
    *eps = fabs((x - x1) / x);
    // printf("Tentativa %d, x = %lf, absx = %lf\n", *it, x, *eps);
  }
  *raiz = x;
  if (*it > MAXIT) return -1;
  return 0;
}


void calcPolinomio_rapido(Polinomio p, double x, double *px, double *dpx) {
  double b = p.p[p.grau];
  // printf("\nb = %lf\n", b);
  double c = b;
  for (int k = p.grau - 1; k; --k) {
    b = p.p[k] + (b * x);
    // printf("\nb = %lf + (%lf * %lf) = %lf\n", c, p.p[k], x, b);
    c = b + (c * x);
    // printf("\nc = %lf + (%lf * %lf) = %lf\n", c, b, x, c);
  }
  b = p.p[0] + (b * x);
  // printf("\nb = %lf + (%lf * %lf) = %lf\n", c, p.p[0], x, b);
  *px = b;
  if (dpx != NULL) *dpx = c;
}


void calcPolinomio_lento(Polinomio p, double x, double *px, double *dpx) {
  double result = 0, deriv = 0;
  double ant = 0, derivAnt = 0;
  for(int i = 0; i <= p.grau; i++) {
    ant = result;
    double power = pow(x,p.grau-i);
    result = result + p.p[i] * power;

    if (i < p.grau) {
      derivAnt = deriv;
      double powerDeriv = pow(x,p.grau-i-1);
      // printf("\npowerDeriv = %lf ^ %d = %lf\n", x, p.grau-i-1,powerDeriv);
      // if (powerDeriv > 1)
        deriv = deriv + ((p.p[i] * p.grau-i) * powerDeriv);
      // else
      //   deriv = deriv + ((p.p[i] * p.grau-i));
      // printf("\nderiv = %lf + (%lf * %d) * %lf = %lf\n", derivAnt, p.p[i], p.grau-i, powerDeriv, deriv);
    }
  }
  *px = result;
  if (dpx != NULL) *dpx = deriv;
}
