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
    double *r = malloc(sizeof(double)*n);
    double *Ax = malloc(sizeof(double)*n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Ax[i] = A[i*n+j] * x[j];
        }
    }
    for (int i = 0; i < n; ++i) {
        r[i] = b[i] - Ax[i]; // r = b - A*x
    }
    double res = 0.0;
    for (int i = 0; i < n; ++i) {
        res += r[i] * r[i];
    }
    free(r);
    free(Ax);
    return sqrt(res);
}

/**
 * Função que inverte uma matriz
 * M: matriz a ser invertida
 * n: ordem da matriz
 **/
inline double* inverseMatrix(double *M, int n) {
    double *V = malloc(sizeof(double)*n*n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (M[i*n+j] == 0) continue;
            V[i*n+j] = 1 / M[i*n+j];
        }
    }
    return V;
}

/**
 * Função que retorna a matrix transposta
 * lines: numero de linhas
 * cols: numero de colunas
 **/
inline double* transposeMatrix(double *A, int lines, int cols) {
    double *T = malloc(sizeof(double)*lines*cols);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < cols; j++) {
            int index = (i * lines) + j;
            int indexT = (j * lines) + i;
            T[indexT] = A[index];
        }
    }
    return T;
}

/**
 * Função que resolve Ax = b utilizando método de gradientes conjugados.
 * A: matriz de coeficientes
 * p: peso
 * b: vetor de termos independentes
 * x: vetor de incógnitas
 * n: ordem da matriz
 * max: número máximo de iterações
 * erro: tolerância aceitável
 * Referências:
 * M. Cristina C. Cunha, Métodos Numéricos, 2ª Edição, Editora Unicamp, 2000.
 **/
int conjGradient(double *A, double p, double *b, double *x,
                     int n, double max, double erro, FILE *fp) {
    double *D = malloc(sizeof(double)*n*n);
    double *L = malloc(sizeof(double)*n*n);
    double *U = malloc(sizeof(double)*n*n);
    double *I = malloc(sizeof(double)*n*n);
    // ----------------------------------------------------------
    // Transformando matriz em simetrica
    printf("Transformando matriz em simetrica...\n");
    double *AT = transposeMatrix(A,n,n);
    double *ATA = malloc(sizeof(double)*n*n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ATA[i*n+j] += A[i*n+k] * AT[k*n+j];
            }
        }
    }
    double *ATb = malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ATb[i] += AT[i*n+j] * b[j];
        }
    }
    // ----------------------------------------------------------
    printf("Coletando D, L, U...\n");
    double startCond = timestamp();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i==j) {
                D[i*n+j] = ATA[i*n+j];
                I[i*n+j] = 1.0;
            } else if (j>i) {
                U[i*n+j] = ATA[i*n+j];
            } else if (j<i) {
                L[i*n+j] = ATA[i*n+j];
            }
        }
    }
    // ----------------------------------------------------------
    printf("Calculando pré-condicionadora...\n");
    double *M;
    if (p == 0.0) M = I;
    else if (p > 0.0 && p < 1.0) M = D;
    else if (p >= 1.0) {
        M = malloc(sizeof(double)*n*n);
        double *Dinv = inverseMatrix(D,n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                M[i*n+j] = (D[i*n+j]+p*L[i*n+j])*Dinv[i*n+j]*(D[i*n+j]+p*U[i*n+j]);
            }
        }
        free(Dinv);
    }
    double endCond = timestamp() - startCond;
    // printf("Matriz M:\n");
    // printMatrix(M,n);
    // ----------------------------------------------------------
    printf("Invertendo matriz condicionadora...\n");
    M = inverseMatrix(M,n); // invertendo M
    // ----------------------------------------------------------
    // Transformando matriz com condicionadora
    // Ax = b → M^−1Ax = M^−1b
    printf("Transformando sistema com condicionadora...\n");
    double *ATAaux = malloc(sizeof(double)*n*n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ATAaux[i*n+j] += M[i*n+k] * ATA[k*n+j];
            }
        }
    }
    free(ATA);
    ATA = ATAaux;

    double *bAux = malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bAux[i] += M[i*n+j] * ATb[j];
        }
    }
    free(ATb);
    ATb = bAux;
    // ----------------------------------------------------------
    printf("Inicializando variáveis...\n");
    // printMatrix(M,n);
    double *r = malloc(sizeof(double)*n);
    double *v = malloc(sizeof(double)*n);
    double *z = malloc(sizeof(double)*n);
    double *y = malloc(sizeof(double)*n);
    double *xant = malloc(sizeof(double)*n); // guardar x anterior
    double aux = 0.0;
    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
        r[i] = ATb[i]; // r = b
        for (int j = 0; j < n; j++) {
            v[i] += M[i*n+j] * ATb[j]; // v = M^-1b
            y[i] += M[i*n+j] * ATb[j]; // y = M^-1r
        }
        aux += y[i] * r[i]; // aux = y^Tr
    }
    // ----------------------------------------------------------
    printf("Iniciando cálculo...\n");
    int k;
    double meanTime = 0.0;
    for (k = 0; k < max; k++) {
        double startTime = timestamp();
        // ----------------------------------------------------------
        // z = Av
        for (int i = 0; i < n; i++) {
            z[i] = 0.0;
            for (int j = 0; j < n; j++) {
                z[i] += ATA[i*n+j] * v[j];
            }
        }
        // ----------------------------------------------------------
        // s = aux/ v^Tz
        double vtz = 0.0;
        for (int i = 0; i < n; i++) {
            vtz += v[i] * z[i];
        }
        double s = aux/vtz;
        // ----------------------------------------------------------
        // x^k+1 = x^k + sv
        for (int i = 0; i < n; i++) {
            xant[i] = x[i];
            x[i] = x[i] + (v[i] * s);
        }
        fprintf(fp, "# iter %d: %.15g\n", k+1, normaMax(x,xant,n));
        // ----------------------------------------------------------
        // r = r - sz
        for (int i = 0; i < n; i++) {
            r[i] = r[i] - (z[i] * s);
        }
        // ----------------------------------------------------------
        // y = M^-1r
        for (int i = 0; i < n; i++) {
            y[i] = 0.0;
            for (int j = 0; j < n; j++) {
                y[i] += M[i*n+j] * r[j];
            }
        }
        // ----------------------------------------------------------
        // rTr = r^Tr
        double rTr = 0.0;
        for (int i = 0; i < n; i++) {
            rTr += r[i] * r[i];
        }
        if (isinf(rTr) || isnan(rTr)) {
            fprintf(stderr, "ERRO: Vetor r chegou a inf ou nan!\n");
            k = -1;
            break;
        }
        // ----------------------------------------------------------
        // aux1 = y^Tr
        double aux1 = 0.0;
        for (int i = 0; i < n; i++) {
            aux1 += y[i] * r[i];
        }
        double m = aux1/aux;
        aux = aux1;
        // ----------------------------------------------------------
        // v = y + mv
        for (int i = 0; i < n; i++) {
            v[i] = y[i] + (v[i] * m);
        }
        // ----------------------------------------------------------
        double endTime = timestamp() - startTime;
        meanTime += endTime;
        printf("residuo = %lf\n", rTr);
        if (rTr < erro) {
            break;
        }
    }
    // printf("meanTime = %lf, k = %d\n", meanTime, k);
    meanTime /= k+1;
    // ----------------------------------------------------------
    double startTime = timestamp();
    double residuo = normaEuc(A,b,x,n);
    double endTime = timestamp() - startTime;
    // ----------------------------------------------------------
    fprintf(fp, "# residuo: %.15g\n", residuo);
    fprintf(fp, "# Tempo iter: %.15g\n", meanTime);
    fprintf(fp, "# Tempo residuo: %.15g\n", endTime);
    fprintf(fp, "# Tempo PC: %.15g\n", endCond);
    // ----------------------------------------------------------
    free(D);
    free(L);
    free(U);
    free(I);
    free(xant);
    free(y);
    free(r);
    free(v);
    free(z);
    return k;
}