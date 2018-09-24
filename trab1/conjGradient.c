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
            r += b[j] - (A[i*n+j] * x[j]); // r = b - A*x
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
            if (M[i*n+j] == 0) continue;
            M[i*n+j] = 1 / M[i*n+j];
        }
    }
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

// inline double* findLower(double *A, int n) {
//     double *L = malloc(sizeof(double)*n*n);
//     for (int i = 0; i < n; i++) {
//         A[i*n+i] = sqrt(A[i*n+i]);
//         for (int j = 0; j < n; j++) {
//             if (A[i*n+j] != 0) A[i*n+j] = A[i*n+j] / A[i*n+i];
//         }
//         for (int j = i+1; j < n; j++) {
//             for (int k = j; k < n; k++) {
//                 if (A[j*n+k] != 0) A[j*n+k] = A[j*n+k] - A[i*n+k] * A[i*n+j];
//             }
//         }
//     }
//     for (int i = 0; i < n; i++) {
//         for (int j = i+1; j < n; j++) {
//             A[i*n+j] = 0.0;
//         }
//     }
// }

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
int conjGradient(double *A, double *M, double *b, double *x,
                     int n, double max, double erro, FILE *fp) {
    // Transformando matriz em simetrica
    printf("Transformando matriz em simetrica...\n");
    double *AT = transposeMatrix(A,n,n);
    double *ATA = malloc(sizeof(double)*n*n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ATA[i*n+j] = A[i*n+j] * AT[i*n+j];
        }
    }
    double *ATb = malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ATb[i] += AT[i*n+j] * b[j];
        }
    }
    inverseMatrix(M,n); // invertendo M
    // Transformando matriz com condicionadora
    // Ax = b → M^−1Ax = M^−1b
    printf("Transformando matriz com condicionadora...\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ATA[i*n+j] = M[i*n+j] * ATA[i*n+j];
        }
    }
    double *bAux = malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bAux[i] += M[i*n+j] * ATb[j];
        }
    }
    free(ATb);
    ATb = bAux;
    printf("Inicializando variáveis...\n");
    // printMatrix(M,n);
    double *r = malloc(sizeof(double)*n);
    double *v = malloc(sizeof(double)*n);
    double *z = malloc(sizeof(double)*n);
    double *y = malloc(sizeof(double)*n);
    double aux = 0.0;
    for (int i = 0; i < n; i++) {
        r[i] = ATb[i]; // r = b
        for (int j = 0; j < n; j++) {
            v[i] += M[i*n+j] * ATb[j]; // v = M^-1b
            y[i] += M[i*n+j] * ATb[j]; // y = M^-1r
        }
        aux += y[i] * r[i]; // aux = y^Tr
    }

    double *xant = malloc(sizeof(double)*n); // guardar x anterior
    printf("Iniciando cálculo...\n");
    int k;
    double meanTime = 0.0;
    for (k = 0; k < max; k++) {
        double startTime = timestamp();
        // z = Av
        for (int i = 0; i < n; i++) {
            z[i] = 0.0;
            for (int j = 0; j < n; j++) {
                z[i] += ATA[i*n+j] * v[j];
            }
        }
        // s = aux/ v^Tz
        double vtz = 0.0;
        for (int i = 0; i < n; i++) {
            vtz += v[i] * z[i];
        }
        double s = aux/vtz;
        // x^k+1 = x^k + sv
        for (int i = 0; i < n; i++) {
            xant[i] = x[i];
            x[i] = x[i] + (v[i] * s);
        }
        fprintf(fp, "# iter %d: %.15g\n", k+1, normaMax(x,xant,n));
        // r = r - sz
        for (int i = 0; i < n; i++) {
            r[i] = r[i] - (z[i] * s);
        }
        // y = M^-1r
        for (int i = 0; i < n; i++) {
            y[i] = 0.0;
            for (int j = 0; j < n; j++) {
                y[i] += M[i*n+j] * r[j];
            }
        }
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
        double aux1 = 0.0;
        // aux1 = y^Tr
        for (int i = 0; i < n; i++) {
            aux1 += y[i] * r[i];
        }
        double m = aux1/aux;
        aux = aux1;
        // v = y + mv
        for (int i = 0; i < n; i++) {
            v[i] = y[i] + (v[i] * m);
        }
        double endTime = timestamp() - startTime;
        meanTime = (meanTime + endTime) / 2;
        printf("residuo = %lf\n", rTr);
        if (rTr < erro) {
            break;
        }
    }
    double startTime = timestamp();
    double residuo = normaEuc(A,b,x,n);
    double endTime = timestamp() - startTime;
    fprintf(fp, "# residuo: %.15g\n", residuo);
    fprintf(fp, "# Tempo iter: %.15g\n", meanTime);
    fprintf(fp, "# Tempo residuo: %.15g\n", endTime);
    free(xant);
    free(y);
    free(r);
    free(v);
    free(z);
    return k;
}