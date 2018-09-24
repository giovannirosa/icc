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

int main(int argc, char *argv[]) {
    srand(20182);
    int n = -1, k = -1, max_it = -1;
    double p = -1.0, e = 0.001;
    char *out = NULL;
    FILE *fp;
    printf("Lendo parâmetros...\n");
    for(int cont=1; cont < argc; cont++) {
        if (strcmp(argv[cont],"-h") == 0) {
            printf("O programa deve ser executado com os seguintes parâmetros:\n");
            printf("cgSolver -n <n> -k <k> -p <ω> -i <i> -e <ε> -o <arquivo_saida>\n");
            printf("<n>: (n>10) parâmetro obrigatório definindo a dimensão do Sistema Linear.\n");
            printf("<k>: (k>1 e k ímpar)  parâmetro obrigatório definindo o número de diagonais da matriz A.\n");
            printf("<ω>: parâmetro obrigatório indicando o pré-condicionador a ser utilizado:\n");
            printf("\tω=0.0: sem pré-condicionador\n");
            printf("\t0.0 < ω < 1.0: pré-condicionador de Jacobi\n");
            printf("<i>: parâmetro obrigatório definindo o número máximo de iterações a serem executadas.\n");
            printf("<ε>: parâmetro opcional definindo o erro aproximado absoluto máximo, considerando a norma max (relativa) em x (max|xi - xi-1| * 1/|xi| < ε).\n");
            printf("<arquivo_saida>: parâmetro obrigatório no qual arquivo_saida é o caminho completo para o arquivo que vai conter a solução.\n");
            return 0;
        }
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
    double *D = malloc(sizeof(double)*n*n);
    double *I = malloc(sizeof(double)*n*n);
    int km = (k+1)/2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i==j || (j>i && j<i+km) || (i>j && i<j+km)) {
                A[i*n+j] = generateRandomA(i,j,k);
                if (i==j) {
                    D[i*n+j] = A[i*n+j];
                    I[i*n+j] = 1.0;
                } else {
                    D[i*n+j] = 0.0;
                    I[i*n+j] = 0.0;
                }
            } else {
                A[i*n+j] = 0.0;
                D[i*n+j] = 0.0;
                I[i*n+j] = 0.0;
            }
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
    printf("Rodando método de gradientes conjugados...\n");
    double *x = malloc(sizeof(double)*n);
    double *M;
    if (p == 0.0) M = I;
    else if (p > 0.0 && p < 1.0) M = D;
    int it = conjGradient(A,M,b,x,n,max_it,e,fp);
    printf("---------------------------------\n");
    if (it >= max_it) {
        fprintf(stderr, "O método extrapolou o limite de %d iterações!\n", max_it);
        free(A);
        free(D);
        free(I);
        free(b);
        free(x);
        return 1;
    } else if (it == -1) {
        free(A);
        free(D);
        free(I);
        free(b);
        free(x);
        return 1;
    } else {
        printf("Método convergiu com sucesso em %d iterações!\n", it+1);
    }
    printf("Valores de x:\n");
    fprintf(fp, "#\n");
    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("%lf ", x[i]);
        fprintf(fp, "%.15g ", x[i]);
    }
    printf("\n");
    free(A);
    free(D);
    free(I);
    free(b);
    free(x);

    return 0;
}