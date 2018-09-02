#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "SistemasLineares.h"

// Método de Jacobi
double  jacobi (double  *A, double *B,  double *X,  int n,
		double *tIteracao, double *tTotal) {
	double err, Xk1;
	for (int k = 0; k < MAXIT; k++) {
		for (int i = 1; i < n; i++) {
			int index = i + (n * i);
			Xk1 = (B[i] - somatorio(X,n,i)) / A[index];
		}
		err = norma(A,B,n);
		if (err < EPS) { 
			*X = Xk1;
			return err;
		} else 
			return -1;
	}
	return -1;
}

// Método de Gauss-Seidel
double  gaussSeidel (double  *A, double *B,  double *X,  int n,
		     double *tIteracao, double *tTotal) {

}

double somatorio(double *X, int n, int i) {
	double soma = 0;
	for (int j = 1; j < n; j++) {
		if (j != i) {
			soma += X[j];
		}
	}
	return soma;
}

double norma(double *X, double *Y, int n) {
	double max = fabs(X[0] - Y[0]);
	for (int i = 1; i < n; i++) {
		double sub = fabs(X[i] - Y[i]);
		if (sub > max)
			max = sub;
	}
	return max;
}


