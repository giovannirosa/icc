#ifndef __CONJGRADIENT_H__
#define __CONJGRADIENT_H__

/**
 * Auxiliar para imprimir vetores
 * a: vetor
 * n: tamanho do vetor
 **/
void printArray(double *a, int n);

/**
 * Auxiliar para imprimir matrizes
 * a: matriz
 * n: ordem da matriz
 **/
void printMatrix(double *a, int n);

/**
 * Função que retorna a norma máxima entre a diferença de dois vetores
 * X,Y: vetores
 * n: tamanho dos vetores
 **/
double normaMax(double *X, double *Y, int n);

/**
 * Função que retorna a norma euclidiana de r, onde r = b - A*x
 * A: matriz de coeficientes
 * b: vetor de termos independentes
 * x: vetor de incógnitas
 * n: ordem da matriz
 **/
double normaEuc(double *A, double *b, double *x, int n);

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
int conjGradient(double *A, double *b, double *x, int n, double max, double erro, FILE *fp);

#endif // __CONJGRADIENT_H__