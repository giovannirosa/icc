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
 * Função que inverte uma matriz
 * M: matriz a ser invertida
 * n: ordem da matriz
 **/
inline void inverseMatrix(double *M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i*n+j] = 1 / M[i*n+j];
        }
    }
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
 * M. Cristina C. Cunha, Métodos Numéricos, 2ª Edição, Editora Unicamp, 2000.
 **/
int conjGradient(double *A, double *M, double *b, double *x, int n, double max, double erro, FILE *fp) {
    printf("Inicializando variáveis...\n");
    inverseMatrix(M,n);
    double *r = malloc(sizeof(double)*n);
    double *v = malloc(sizeof(double)*n);
    double *z = malloc(sizeof(double)*n);
    double aux = 0;
    for (int i = 0; i < n; i++) {
        
        for (int i = 0; i < n; i++) {

        }
        x[i] = 0.0; // x^0 = 0
        r[i] = b[i]; // r = b
        v[i] = b[i]; // v = M^-1b
        aux += b[i] * b[i]; // aux = r^Tr
    }

    double *xant = malloc(sizeof(double)*n); // guardar x anterior
    printf("Iniciando cálculo...\n");
    int k;
    for (k = 0; k < max; k++) {
        // z = Av
        for (int i = 0; i < n; i++) {
            z[i] = 0.0;
            for (int j = 0; j < n; j++) {
                int index = (i * n) + j;
                z[i] += A[index] * v[j];
            }
        }
        // s = aux/ v^Tz
        double vtz = 0;
        for (int i = 0; i < n; i++) {
            vtz += v[i] * z[i];
        }
        double s = aux/vtz;
        // x^k+1 = x^k + sv
        for (int i = 0; i < n; i++) {
            xant[i] = x[i];
            x[i] = x[i] + (v[i] * s);
        }
        fprintf(fp, "# iter %d: <%.15g>\n", k+1, normaMax(x,xant,n));
        // r = r - sz
        for (int i = 0; i < n; i++) {
            r[i] = r[i] - (z[i] * s);
        }
        // aux1 = r^Tr
        double aux1 = 0;
        for (int i = 0; i < n; i++) {
            aux1 += r[i] * r[i];
        }
        if (isinf(aux1) || isnan(aux1)) {
            fprintf(stderr, "ERRO: Vetor r chegou a inf ou nan!\n");
            k = -1;
            break;
        }
        printf("residuo = %lf\n", aux1);
        if (aux1 < erro) {
            break;
        }
        double m = aux1/aux;
        aux = aux1;
        // v = r + mv
        for (int i = 0; i < n; i++) {
            v[i] = r[i] + (v[i] * m);
        }
    }
    free(xant);
    free(r);
    free(v);
    free(z);
    return k;
}