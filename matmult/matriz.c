#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"

/**
 * Função que gera os coeficientes de um sistema linear k-diagonal
 * @param i,j coordenadas do elemento a ser calculado (0<=i,j<n)
 * @param k numero de diagonais da matriz A
 */
static inline double generateRandomA( unsigned int i, unsigned int j, unsigned int k )
{
  static double invRandMax = 1.0 / (double)RAND_MAX;
  return ( (i==j) ? (double)(k<<1) : 1.0 )  * (double)rand() * invRandMax;
}

/**
 * Função que gera os termos independentes de um sistema linear k-diagonal
 * @param k numero de diagonais da matriz A
 *
 */
static inline double generateRandomB( unsigned int k )
{
  static double invRandMax = 1.0 / (double)RAND_MAX;
  return (double)(k<<2) * (double)rand() * invRandMax;
}



/* ----------- FUNÇÕES ---------------- */

/**
 *  Funcao geraMatPtr: gera matriz como vetor de ponteiros para as suas linhas
 * 
 *  @param m  número de linhas da matriz
 *  @param n  número de colunas da matriz
 *  @return  ponteiro para a matriz gerada
 *
 */

MatPtr geraMatPtr (int m, int n)
{
  MatPtr matriz = (double **) malloc(m*sizeof(double));

  if (matriz) {
    for (int i=0; i < m; ++i) {
      if (matriz[i] = (double *) malloc(n*sizeof(double)))
	for (int j=0; matriz[i] && j < n; ++j)
	  matriz[i][j] = generateRandomA(i, j, m*n );
      else
	return NULL;
    }
  }
  
  return (matriz);
}

/**
 *  Funcao geraMatRow: gera matriz como vetor único, 'row-oriented'
 * 
 *  @param m  número de linhas da matriz
 *  @param n  número de colunas da matriz
 *  @return  ponteiro para a matriz gerada
 *
 */

MatRow geraMatRow (int m, int n)
{
  MatRow matriz = (double *) malloc(m*n*sizeof(double));

  if (matriz) {
    for (int i=0; i < m; ++i) {
      for (int j=0; j < n; ++j)
	matriz[m*i + j] = generateRandomA(i, j, m*n);
    }
  }
  
  return (matriz);
}


/**
 *  Funcao geraMatCol: gera matriz como vetor único, 'column-oriented'
 * 
 *  @param m  número de linhas da matriz
 *  @param n  número de colunas da matriz
 *  @return  ponteiro para a matriz gerada
 *
 */

MatCol geraMatCol (int m, int n)
{
  MatCol matriz = (double *) malloc(m*n*sizeof(double));

  if (matriz) {
    for (int i= 0; i < m; ++i) {
      for (int j=0; j < n; ++j)
	matriz[n*j + i] = generateRandomA(i, j, m*n );
    }
  }
  
  return (matriz);
}


/**
 *  Funcao geraVetor: gera vetor de tamanho 'n'
 * 
 *  @param n  número de elementos do vetor
 *  @return  ponteiro para vetor gerado
 *
 */

Vetor geraVetor (int n)
{
  Vetor vetor = (double *) malloc(n*sizeof(double));

  if (vetor)
    for (int i=0; i < n; ++i)
      vetor[i] = generateRandomB(n);
  
  return (vetor);
}


/**
 *  Funcao multMatPtrVet:  Efetua multiplicacao entre matriz 'mxn' por vetor
 *                       de 'n' elementos
 *  @param mat matriz 'mxn'
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *  @param res vetor que guarda o resultado. Deve estar previamente alocado e com
 *             seus elementos inicializados em 0.0 (zero)
 *  @return vetor de 'm' elementos
 *
 */

void multMatPtrVet (MatPtr mat, Vetor v, int m, int n, Vetor res)
{
    
  /* Efetua a multiplicação */
  if (res) {
    for (int i=0; i < m; ++i)
      for (int j=0; j < n; ++j)
	  res[i] += mat[i][j] * v[j];
  }
}

/**
 *  Funcao prnMatPtr:  Imprime o conteudo de uma matriz em stdout
 *  @param mat matriz
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *
 */

void prnMatPtr (MatPtr mat, int m, int n)
{
  for (int i=0; i < m; ++i) {
    for (int j=0; j < n; ++j)
      printf(DBL_FIELD, mat[i][j]);
    printf("\n");
  }
  printf(SEP_RES);
}

/**
 *  Funcao multMatRowVet:  Efetua multiplicacao entre matriz 'mxn' por vetor
 *                       de 'n' elementos
 *  @param mat matriz 'mxn'
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *  @param res vetor que guarda o resultado. Deve estar previamente alocado e com
 *             seus elementos inicializados em 0.0 (zero)
 *  @return vetor de 'm' elementos
 *
 */

void multMatRowVet (MatRow mat, Vetor v, int m, int n, Vetor res)
{
    
  /* Efetua a multiplicação */
  if (res) {
    for (int i=0; i < m; ++i)
      for (int j=0; j < n; ++j)
	  res[i] += mat[m*i + j] * v[j];
  }
}

/**
 *  Funcao prnMatRow:  Imprime o conteudo de uma matriz em stdout
 *  @param mat matriz
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *
 */

void prnMatRow (MatRow mat, int m, int n)
{
  for (int i=0; i < m; ++i) {
    for (int j=0; j < n; ++j)
      printf(DBL_FIELD, mat[m*i + j]);
    printf("\n");
  }
  printf(SEP_RES);
}

/**
 *  Funcao multMatColVet:  Efetua multiplicacao entre matriz 'mxn' por vetor
 *                       de 'n' elementos
 *  @param mat matriz 'mxn'
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *  @param res vetor que guarda o resultado. Deve estar previamente alocado e com
 *             seus elementos inicializados em 0.0 (zero)
 *  @return vetor de 'm' elementos
 *
 */

void multMatColVet (MatCol mat, Vetor v, int m, int n, Vetor res)
{
    
  /* Efetua a multiplicação */
  if (res) {
    for (int i=0; i < m; ++i)
      for (int j=0; j < n; ++j)
	  res[i] += mat[n*j + i] * v[j];
  }
}

/**
 *  Funcao prnMatCol:  Imprime o conteudo de uma matriz em stdout
 *  @param mat matriz
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *
 *
 */

void prnMatCol (MatCol mat, int m, int n)
{
  for (int i=0; i < m; ++i) {
    for (int j=0; j < n; ++j)
      printf(DBL_FIELD, mat[n*j + i]);
    printf("\n");
  }

  printf(SEP_RES);

}

/**
 *  Funcao prodEscalar:  Calcula o produto escalar entre 2 vetores
 *  @param v1 vetor com 'n' elementos
 *  @param v2 vetor com 'n' elementos
 *  @param n número de elementos dos vetores
 *  @return Valor do produto escalar
 */

double prodEscalar (Vetor v1, Vetor v2, int n)
{
  double prod = 0.0;

  for (int i=0; i < n; ++i)
    prod += v1[i]*v2[i];

  return prod;
}


/**
 *  Funcao normaMax:  Calcula a norma máxima da diferença de 2 vetores
 *  @param v1 vetor com 'n' elementos
 *  @param v2 vetor com 'n' elementos
 *  @param n número de elementos dos vetores
 *  @return Valor da norma máxima
 */

double normaMax (Vetor v1, Vetor v2, int n)
{
  double max = ABS(v1[0] - v2[0]);

  for (int i=0; i < n; ++i)
    if (ABS(v1[i]-v2[i]) > max)
      max = ABS(v1[i]-v2[i]);

  return max;
}


/**
 *  Funcao normaEucl:  Calcula a norma euclidiana de um vetor
 *  @param vet vetor com 'n' elementos
 *  @param n número de elementos dos vetores
 *  @return Valor da norma euclidiana
 */

double normaEucl (Vetor vet, int n)
{
  double prod = 0.0;

  for (int i=0; i < n; ++i)
    prod += vet[i]*vet[i];

  return sqrt(prod);
}


/**
 *  Funcao prnVetor:  Imprime o conteudo de vetor em stdout
 *  @param vet vetor com 'n' elementos
 *  @param n número de elementos do vetor
 *
 */

void prnVetor (Vetor vet, int n)
{
  for (int i=0; i < n; ++i)
    printf(DBL_FIELD, vet[i]);
  printf(SEP_RES);
}

