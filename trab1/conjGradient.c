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
            printf("%.2lf ", a[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Auxiliar para imprimir matrizes
 * a: matriz
 * n: ordem da matriz
 * k: numero de diagonais
 **/
inline void printMatrixDiagonal(matrix *a, int n) {
    int km = (a->diag+1)/2;
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i==j || (j>i && j<i+km) || (i>j && i<j+km)) {
                printf("%lf ", a->nodes[index++]->val);
            } else {
                printf("0.000000 ");
            }
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
inline double normaEuc(matrix *A, double *b, double *x, int n) {
    double *r = malloc(sizeof(double)*n);
    double *Ax = malloc(sizeof(double)*n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Ax[i] = findVal(A,i,j) * x[j];
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
inline void inverseMatrix(matrix *M, int n) {
    for (int i = 0; i < n; i++) {
        if (M->nodes[i]->val != 0)
            M->nodes[i]->val = 1/M->nodes[i]->val;
    }
}

/**
 * Função que retorna a matrix transposta
 * lines: numero de linhas
 * cols: numero de colunas
 **/
inline double* transposeMatrix(double *A, int n) {
    double *T = malloc(sizeof(double)*n*n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int index = (i * n) + j;
            int indexT = (j * n) + i;
            T[indexT] = A[index];
        }
    }
    return T;
}

/**
 * Função que retorna a matrix transposta
 * lines: numero de linhas
 * cols: numero de colunas
 **/
// inline double* transposeMatrixDiagonal(matrix *A, int n) {
//     // double *Aaux = malloc(sizeof(double)*n*n);
//     // int km = (k+1)/2;
//     // int index = 0;
//     // for (int i = 0; i < n; i++) {
//     //     for (int j = 0; j < n; j++) {
//     //         if (i==j || (j>i && j<i+km) || (i>j && i<j+km)) {
//     //             Aaux[i*n+j] = A[index++];
//     //         } else {
//     //             Aaux[i*n+j] = 0.0;
//     //         }
//     //     }
//     // }
//     // double *Taux = transposeMatrix(Aaux,n);
//     // free(Aaux);
//     // index = 0;
//     double *T = malloc(sizeof(double)*);
//     // for (int i = 0; i < n; i++) {
//     //     for (int j = 0; j < n; j++) {
//     //         if (i==j || (j>i && j<i+km) || (i>j && i<j+km)) {
//     //             T[index++] = Taux[i*n+j];
//     //         }
//     //     }
//     // }
//     // free(Taux);
//     return T;
// }

double findVal(matrix *A, int line, int col) {
    for (int i = 0; i < A->size; ++i) {
        node *n = A->nodes[i];
        if (n->line == line && n->col == col) {
            return n->val;
        }
    }
    return 0.0;
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
int conjGradient(matrix *A, double p, double *b, double *x,
                     int n, double max, double erro, FILE *fp) {
    // ----------------------------------------------------------
    // Transformando matriz em simetrica
    printf("Transformando matriz em simetrica...\n");
    // double *AT = transposeMatrixDiagonal(A,n);
    matrix *ATA = malloc(sizeof(matrix));
    ATA->nodes = malloc(sizeof(node)*A->size);
    ATA->size = A->size;
    ATA->diag = A->diag;
    int km = (A->diag+1)/2;
    int index = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i==j || (j>i && j<i+km) || (i>j && i<j+km)) {
                node *no = malloc(sizeof(node));
                no->line = i;
                no->col = j;
                no->val = 0.0;
                // printf("********(%d,%d)\n",i,j);
                for (int l = 0; l < n; ++l) {
                    if (i==l || j==l || 
                    (l>i && l<i+km) || (i>l && i<l+km) ||
                    (l>j && l<j+km) || (j>l && j<l+km)) {
                        double val1 = findVal(A,i,l);
                        double val2 = findVal(A,j,l);
                        // printf("val = %lf + %lf(%d,%d) * %lf(%d,%d)\n", no->val,val1,i,l,val2,j,l);
                        no->val += val1 * val2;
                    }
                }
                // printf("********\n");
                ATA->nodes[index++] = no;
            }
        }
    }
    // printMatrixDiagonal(ATA,n);

    double *ATb = malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++) {
        // printf("********(%d)\n",i);
        for (int j = 0; j < n; j++) {
            if (i==j || (j>i && j<i+km) || (i>j && i<j+km)) {
                double val1 = findVal(A,j,i);
                // printf("val = %lf + %lf(%d,%d) * %lf(%d)\n", ATb[i],val1,i,j,b[j],j);
                ATb[i] += val1 * b[j];
            }
        }
        // printf("********\n");
    }
    // printArray(ATb,n);
    // ----------------------------------------------------------
    printf("Calculando pré-condicionadora...\n");
    double startCond = timestamp();
    matrix *M = malloc(sizeof(matrix));
    M->nodes = malloc(sizeof(node)*n);
    M->size = n;
    M->diag = 1;
    if (p == 0.0) { // Matriz Identidade
        for (int i = 0; i < n; i++) {
            node *no = malloc(sizeof(node));
            no->line = i;
            no->col = i;
            no->val = 1.0;
            M->nodes[i] = no;
        }
    } else if (p > 0.0 && p < 1.0) { // Matriz Diagonal
        int dIndex = 0;
        index = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i==j) {
                    // printf("dIndex = %d | index = %d\n", dIndex,index);
                    node *no = malloc(sizeof(node));
                    no->line = i;
                    no->col = j;
                    no->val = ATA->nodes[index++]->val;
                    M->nodes[dIndex++] = no;
                } else if ((j>i && j<i+km) || (i>j && i<j+km)) {
                    ++index;
                }
            }
        }
    }
    double endCond = timestamp() - startCond;
    // printf("Matriz M:\n");
    // printMatrixDiagonal(M,n);
    // ----------------------------------------------------------
    printf("Invertendo matriz condicionadora...\n");
    inverseMatrix(M,n); // invertendo M
    // printMatrixDiagonal(M,n);
    // ----------------------------------------------------------
    // Transformando matriz com condicionadora
    // Ax = b → M^−1Ax = M^−1b
    printf("Transformando sistema com condicionadora...\n");
    // matrix *ATAaux = malloc(sizeof(matrix));
    // ATAaux->nodes = malloc(sizeof(node)*ATA->size);
    // ATAaux->size = ATA->size;
    // ATAaux->diag = ATA->diag;
    // index = 0;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         if (i==j || (j>i && j<i+km) || (i>j && i<j+km)) {
    //             node *no = malloc(sizeof(node));
    //             no->line = i;
    //             no->col = j;
    //             no->val = 0.0;
    //             // printf("********(%d,%d)\n",i,j);
    //             for (int l = 0; l < n; l++) {
    //                 if (i==l && (j==l ||
    //                 (l>j && l<j+km) || (j>l && j<l+km))) {
    //                     double val1 = findVal(M,i,l);
    //                     double val2 = findVal(ATA,l,j);
    //                     // printf("val = %lf + %lf(%d,%d) * %lf(%d,%d)\n", no->val,val1,i,l,val2,l,j);
    //                     no->val += val1 * val2;
    //                 }
    //             }
    //             // printf("********\n");
    //             ATAaux->nodes[index++] = no;
    //         }
    //     }
    // }
    // free(ATA);
    // ATA = ATAaux;
    // printMatrixDiagonal(ATA,n);

    // double *bAux = malloc(sizeof(double)*n);
    // for (int i = 0; i < n; i++) {
    //     bAux[i] = M->nodes[i]->val * ATb[i];
    // }
    // free(ATb);
    // ATb = bAux;
    // printArray(ATb,n);
    // ----------------------------------------------------------
    printf("Inicializando variáveis...\n");
    double *r = malloc(sizeof(double)*n);
    double *v = malloc(sizeof(double)*n);
    double *z = malloc(sizeof(double)*n);
    double *y = malloc(sizeof(double)*n);
    double *xant = malloc(sizeof(double)*n); // guardar x anterior
    double aux = 0.0;
    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
        r[i] = ATb[i]; // r = b
        v[i] = M->nodes[i]->val * ATb[i]; // v = M^-1b
        y[i] = M->nodes[i]->val * r[i]; // y = M^-1r
        aux += y[i] * r[i]; // aux = y^Tr
    }
    // printArray(v,n);
    // printArray(y,n);
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
                if (i==j || (j>i && j<i+km) || (i>j && i<j+km)) {
                    z[i] += findVal(ATA,i,j) * v[j];
                }
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
            x[i] += (v[i] * s);
        }
        fprintf(fp, "# iter %d: %.15g\n", k+1, normaMax(x,xant,n));
        // ----------------------------------------------------------
        // r = r - sz
        for (int i = 0; i < n; i++) {
            r[i] -= (z[i] * s);
        }
        // ----------------------------------------------------------
        // y = M^-1r
        for (int i = 0; i < n; i++) {
            y[i] = M->nodes[i]->val * r[i];
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
    free(M);
    free(xant);
    free(y);
    free(r);
    free(v);
    free(z);
    return k;
}