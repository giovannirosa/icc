#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "conjGradient.h"
#include "utils.h"

/**
 * Auxiliar para imprimir vetores
 * a: vetor
 * n: tamanho do vetor
 **/
inline void printArray(double *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lf ", a[i]);
    }
    printf("\n");
}

/**
 * Auxiliar para imprimir matrizes
 * a: matriz
 * n: ordem da matriz
 **/
inline void printMatrix(double *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", a[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Função que retorna a norma máxima entre a diferença de dois vetores
 * X,Y: vetores
 * n: tamanho dos vetores
 **/
inline double normaMax(double *X, double *Y, int n) {
	double max = fabs(X[0] - Y[0]);
	for (int i = 0; i < n; i++) {
		double sub = fabs(X[i] - Y[i]);
		if (sub > max)
			max = sub;
	}
	return max;
}

/**
 * Função que retorna a norma euclidiana de r, onde r = b - A*x
 * A: matriz de coeficientes
 * b: vetor de termos independentes
 * x: vetor de incógnitas
 * n: ordem da matriz
 **/
inline double normaEuc(double *A, double *b, double *x, int n) {
    double max = 0.0;
    for (int i = 0; i < n; i++) {
        double r = 0.0;
        for (int j = 0; j < n; j++) {
            r += (A[i*n+j] * x[i]) - b[i]; // r = A*x - b
        }
        if (r > max)
            max = r;
    }
    return max;
}


/**
 * Função que resolve Ax = b utilizando método de gradientes conjugados.
 * A: matriz de coeficientes
 * b: vetor de termos independentes
 * x: vetor de incógnitas
 * n: ordem da matriz
 * max: número máximo de iterações
 * erro: tolerância aceitável
 * Referências:
 * https://en.wikipedia.org/wiki/Conjugate_gradient_method
 * https://gist.github.com/sfujiwara/b135e0981d703986b6c2
 **/
int conjGradient(double *A, double *b, double *x, int n, 
                double max, double erro, FILE *fp) {
    double *r = malloc(sizeof(double)*n);
    double *p = malloc(sizeof(double)*n);
    double rsold = 0.0;
    for (int i = 0; i < n; i++) {
        r[i] = 0.0;
        for (int j = 0; j < n; j++) {
            r[i] += (A[i*n+j] * x[i]) - b[i]; // r = A*x - b
        }
        p[i] = -r[i]; // p = -r
        rsold += r[i] * r[i]; // rsold = r^T*r
        x[i] = 0.0;
    }
    printf("Resíduo: %lf\n", rsold);

    double *Ap = malloc(sizeof(double)*n);
    double *xant = malloc(sizeof(double)*n);
    int k;
    for (k = 0; k < max; k++) {
        for (int i = 0; i < n; i++) {
            Ap[i] = 0.0;
            for (int j = 0; j < n; j++) {
                Ap[i] += A[i*n+j] * p[i]; // Ap = A*p
            }
        }
        double pTAp = 0.0;
        for (int i = 0; i < n; i++) {
            pTAp += p[i] * Ap[i]; // p^T*Ap
        }
        double alpha = rsold/pTAp; // alpha = rsold / p^T*Ap
        double rsnew = 0.0;
        for (int i = 0; i < n; i++) {
            xant[i] = x[i];
            x[i] += (alpha * p[i]); // x = x + alpha * p;
            r[i] += (alpha * Ap[i]); // r = r + alpha * Ap;
            rsnew += r[i] * r[i]; // rsnew = r^T * r;
        }
        fprintf(fp, "# iter %d: <%.15g>\n", k+1, normaMax(x,xant,n));
        printf("Resíduo: %lf\n", rsnew);
        if (isnan(rsnew) || isinf(rsnew)) {
            fprintf(stderr, "ERRO: Resíduo chegou a inf ou nan!\n");
            break;
        }
        if (rsnew < erro) {
            break;
        }
        for (int i = 0; i < n; i++) {
            p[i] = ((rsnew/rsold) * p[i]) - r[i]; // p = (rsnew / rsold) * p - r;
        }
        rsold = rsnew;
    }
    fprintf(fp, "# residuo: <%.15g>\n", normaEuc(A,b,x,n));
    free(r);
    free(p);
    free(Ap);
    return k;
}