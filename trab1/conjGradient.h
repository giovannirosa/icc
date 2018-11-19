#ifndef __CONJGRADIENT_H__
#define __CONJGRADIENT_H__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <likwid.h>

static const int DEBUGMSG = 0;

typedef struct node node;

struct node {
    double val;
    int line;
    int col;
};

typedef struct matrix matrix;

struct matrix {
    node **nodes;
    int size;
    int diag;
};

/**
 * Auxiliar para imprimir vetores
 * a: vetor
 * n: tamanho do vetor
 */
void printArray(double *a, int n);

/**
 * Auxiliar para imprimir matrizes
 * a: matriz
 * n: ordem da matriz
 */
void printMatrix(double *a, int n);

/**
 * Auxiliar para imprimir matrizes
 * a: matriz
 * n: ordem da matriz
 * k: numero de diagonais
 **/
void printMatrixDiagonal(matrix *a, int n);

/**
 * Função que retorna a norma máxima entre a diferença de dois vetores
 * X,Y: vetores
 * n: tamanho dos vetores
 */
double normaMax(double *X, double *Y, int n);

/**
 * Função que retorna a norma euclidiana de r, onde r = b - A*x
 * A: matriz de coeficientes
 * b: vetor de termos independentes
 * x: vetor de incógnitas
 * n: ordem da matriz
 */
double normaEuc(matrix *A, double *b, double *x, int n);

/**
 * Função que inverte uma matriz
 * M: matriz a ser invertida
 * n: ordem da matriz
 **/
void inverseMatrix(matrix *M, int n);

/**
 * Função que retorna a matrix transposta
 * lines: numero de linhas
 * cols: numero de colunas
 **/
double* transposeMatrix(double *A, int n);

/**
 * Encontra valor na matriz para posição (line,col)
 * A: matriz para busca
 * line: linha da posição
 * col: coluna da posição
 **/
double findVal(matrix *A, int line, int col);

/**
 * Libera matriz da memória
 * A: matriz a ser liberada
 **/
void freeMatrix(matrix *A);

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
 */
int conjGradient(matrix *A, double p, double *b, double *x, int n, 
                    double max, double erro, FILE *fp);

#endif // __CONJGRADIENT_H__