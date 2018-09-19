#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "conjGradient.h"

#define TRUE 1
#define FALSE 0

/***********************
 * Função que gera os coeficientes de um sistema linear k-diagonal
 * i,j: coordenadas do elemento a ser calculado (0<=i,j<n)
 * k: numero de diagonais da matriz A
 ***********************/
inline static double generateRandomA( unsigned int i, unsigned int j, unsigned int k ) {
  static double invRandMax = 1.0 / (double)RAND_MAX;
  return ( (i==j)?(double)(k<<1) : 1.0 )  * (double)rand() * invRandMax;
}

/***********************
 * Função que gera os termos independentes de um sistema linear k-diagonal
 * k: numero de diagonais da matriz A
 ***********************/
inline static double generateRandomB( unsigned int k ) {
  static double invRandMax = 1.0 / (double)RAND_MAX;
  return (double)(k<<2) * (double)rand() * invRandMax;
}

/**
 * Função que retorna a matrix transposta
 * lines: numero de linhas
 * cols: numero de colunas
 **/
double* transposeMatrix(double *A, int lines, int cols) {
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

int main(int argc, char *argv[]) {
    srand(20182);
    int n = -1, k = -1, max_it = -1;
    double p = -1.0, e = 0.001;
    char *out = NULL;
    FILE *fp;
    printf("Lendo parâmetros...\n");
    for(int cont=0; cont < argc; cont++) {
        if (strcmp(argv[cont],"-n") == 0) {
            n = (int) strtol(argv[++cont], (char **)NULL, 10);
            if (n <= 10) {
                fprintf(stderr, "ERRO: Parâmetro n deve ser maior que 10!\n");
                return 1;
            }
        }
        if (strcmp(argv[cont],"-k") == 0) {
            k = (int) strtol(argv[++cont], (char **)NULL, 10);
            if (k <= 1 || k % 2 == 0) {
                fprintf(stderr, "ERRO: Parâmetro k deve ser maior que 1 e ímpar!\n");
                return 1;
            }
        }
        if (strcmp(argv[cont],"-p") == 0) {
            p = strtof(argv[++cont], (char **)NULL);
            if (p < 0 && p > 2.0) {
                fprintf(stderr, "ERRO: Parâmetro p deve estar entre 0.0 e 2.0!\n");
                return 1;
            }
        }
        if (strcmp(argv[cont],"-i") == 0) {
            max_it = (int) strtol(argv[++cont], (char **)NULL, 10);
        }
        if (strcmp(argv[cont],"-e") == 0) {
            e = strtof(argv[++cont], (char **)NULL);
        }
        if (strcmp(argv[cont],"-o") == 0) {
            out = argv[++cont];
        }
    }
    if (n == -1 || k == -1 || p == -1.0 || max_it == -1 || out == NULL) {
        fprintf(stderr, "ERRO: Parâmetros 'n, k, p, i, o' são obrigatórios!\n");
        return 1;
    }

    printf("n = %d\n", n);
    printf("k = %d\n", k);
    printf("p = %lf\n", p);
    printf("i = %d\n", max_it);
    printf("e = %lf\n", e);
    printf("o = %s\n", out);
    printf("---------------------------------\n");
    fp = fopen(out,"w");
    fprintf(fp, "# grs14 Giovanni Rosa\n");
    fprintf(fp, "#\n");

    // Gerando matriz de coeficientes A
    printf("Gerando matriz de coeficientes A...\n");
    double *A = malloc(sizeof(double)*n*n);
    int km = (k+1)/2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i==j || (j>i && j<i+km) || (i>j && i<j+km))
                A[i*n+j] = generateRandomA(i,j,k);
            else
                A[i*n+j] = 0.0;
        }
    }
    printf("---------------------------------\n");

    // Gerando vetor de termos independentes B
    printf("Gerando vetor de termos independentes B...\n");
    double *b = malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++) {
        b[i] = generateRandomB(k);
    }
    printf("\n---------------------------------\n");
    // Transformando matriz em simetrica
    printf("Transformando matriz em simetrica...\n");
    double *AT = transposeMatrix(A,n,n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i*n+j] = A[i*n+j] * AT[i*n+j];
        }
    }
    printf("Matriz de coeficientes:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", A[i*n+j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        double res = 0.0;
        for (int j = 0; j < n; j++) {
            res += b[i] * A[i*n+j];
        }
        b[i] = res;
    }
    printf("Termos independentes:\n");
    for (int i = 0; i < n; i++) {
        printf("%lf ", b[i]);
    }
    printf("\n---------------------------------\n");
    printf("Rodando método de gradientes conjugados...\n");
    double *x = malloc(sizeof(double)*n);
    int it = conjGradient(A,b,x,n,max_it,e,fp);
    printf("---------------------------------\n");
    if (it >= max_it) {
        fprintf(stderr, "O método extrapolou o limite de %d iterações!\n", max_it);
        free(A);
        free(b);
        free(x);
        free(AT);
        return 1;
    } else if (it == -1) {
        free(A);
        free(b);
        free(x);
        free(AT);
        return 1;
    } else {
        printf("Método convergiu com sucesso em %d iterações!\n", it);
    }
    printf("Valores de x:\n");
    for (int i = 0; i < n; i++) {
        printf("%lf ", x[i]);
    }
    printf("\n");
    free(A);
    free(b);
    free(x);
    free(AT);

    return 0;
}