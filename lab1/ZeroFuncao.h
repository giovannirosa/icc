#ifndef __ZEROFUNCAO_H__
#define __ZEROFUNCAO_H__

// Aproximação aceitável como valor zero
#define ZERO 1.0e-20

// Parâmetros para teste de convergência
#define MAXIT 500
#define EPS 1.0e-8

typedef struct {
  double *p;
  int grau;
} Polinomio;

// Métodos
double bisseccao (Polinomio p, double a, double b, double eps, int *it, double *raiz);
double newtonRaphson (Polinomio p, double x0, double eps, int *it, double *raiz);
double secante (Polinomio p, double x0, double x1, double eps, int *it, double *raiz);

// Cálculo de Polinômios
void calcPolinomio_rapido(Polinomio p, double x, double *px, double *dpx );
void calcPolinomio_lento(Polinomio p, double x, double *px, double *dpx );

#endif // __ZEROFUNCAO_H__

