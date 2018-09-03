#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "SistemasLineares.h"

// Método de Jacobi
double  jacobi (double  *A, double *B,  double *X,  int n,
		double *tIteracao, double *tTotal) {
	double err;
	double *Xk = malloc(sizeof(double)*n);
	double *Xk1 = malloc(sizeof(double)*n);
	for(int i = 0; i < n; i++) { 
		Xk[i] = X[i];
	}
	for (int k = 0; k < MAXIT; k++) {
		double startTime = timestamp();
		for (int i = 0; i < n; i++) {
			int index = i + (n * i);
			Xk1[i] = (B[i] - somatorio(A,Xk,n,i)) / A[index];
		}
		err = norma(Xk1,Xk,n);
		double endTime = timestamp() - startTime;
		*tTotal += endTime;
		*tIteracao = *tTotal / k;
		if (err < EPS) {
			X = Xk1;
			return err;
		}
		for(int i = 0; i < n; i++) { 
			Xk[i] = Xk1[i];
		}
	}
	return -1.0;
}

// Método de Gauss-Seidel
double  gaussSeidel (double  *A, double *B,  double *X,  int n,
		     double *tIteracao, double *tTotal) {
	double err;
	double *Xk = malloc(sizeof(double)*n);
	double *Xk1 = malloc(sizeof(double)*n);
	for(int i = 0; i < n; i++) { 
		Xk[i] = X[i];
	}
	for (int k = 0; k < MAXIT; k++) {
		double startTime = timestamp();
		for (int i = 0; i < n; i++) {
			double soma1 = 0;
			for (int j = 0; j < i; j++) {
				int indexAij = j + (n * i);
				soma1 += A[indexAij] * Xk1[j];
			}
			double soma2 = 0;
			for (int j = i+1; j < n; j++) {
				int indexAij = j + (n * i);
				soma2 += A[indexAij] * Xk[j];
			}
			int indexAii = i + (n * i);
			Xk1[i] = (B[i] - soma1 - soma2) / A[indexAii];
		}
		err = norma(Xk1,Xk,n);
		double endTime = timestamp() - startTime;
		*tTotal += endTime;
		*tIteracao = *tTotal / k;
		if (err < EPS) {
			X = Xk1;
			return err;
		}
		for(int i = 0; i < n; i++) { 
			Xk[i] = Xk1[i];
		}
	}
	return -1.0;
}

double somatorio(double *A, double *X, int n, int i) {
	double soma = 0;
	for (int j = 1; j < n; j++) {
		if (j != i) {
			int index = j + (n * i);
			soma += A[index] * X[j];
		}
	}
	return soma;
}

double norma(double *X, double *Y, int n) {
	double max = fabs(X[0] - Y[0]);
	for (int i = 0; i < n; i++) {
		double sub = fabs(X[i] - Y[i]);
		if (sub > max)
			max = sub;
	}
	return max;
}

double sassenfeld(double *A, int n) {
	double *Beta = malloc(sizeof(double)*n);
	double max = 0;
	for (int i = 0; i < n; i++) {
		double soma1 = 0;
		for (int j = 0; j < i; j++) {
			int indexAij = j + (n * i);
			soma1 += fabs(A[indexAij]) * Beta[j];
		}
		double soma2 = 0;
		for (int j = i+1; j < n; j++) {
			int indexAij = j + (n * i);
			soma2 += fabs(A[indexAij]);
		}
		int indexAii = i + (n * i);
		Beta[i] = (soma1 + soma2) / A[indexAii];
		if (Beta[i] > max)
			max = Beta[i];
	}
	return max;
}
