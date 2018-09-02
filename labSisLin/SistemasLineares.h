#ifndef __SISLINEAR_H__
#define __SISLINEAR_H__

// Parâmetros para teste de convergência
#define MAXIT 500
#define EPS 1.0e-4

// Método de Jacobi
double  jacobi (double  *A, double *B,  double *X,  int n,
		double *tIteracao, double *tTotal);

// Método de Gauss-Seidel
double  gaussSeidel (double  *A, double *B,  double *X,  int n,
		     double *tIteracao, double *tTotal);

#endif // __SISLINEAR_H__

