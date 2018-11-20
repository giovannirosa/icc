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
    double *Ax = malloc(sizeof(double)*n);
    double res = 0.0;
    int rest = n % 4;
    int km = (A->diag+1)/2;
    int limit, j;
    for (int i = 0; i < n-rest; i += 4) {
        if (i < km) {
            j = 0;
            limit = km+i;
        } else {
            j = i-km+1;
            limit = n;
        }
        Ax[i] = Ax[i+1] = Ax[i+2] = Ax[i+3] = 0.0;
        for (; j < limit; ++j) {
            if (i==j || (j>i && j<i+km) || (i>j && i<j+km)) {
                Ax[i] += findVal(A,i,j) * x[j];
                Ax[i+1] += findVal(A,i+1,j) * x[j];
                Ax[i+2] += findVal(A,i+2,j) * x[j];
                Ax[i+3] += findVal(A,i+3,j) * x[j];
            }
        }
        double r = b[i] - Ax[i]; // r = b - A*x
        res += r * r;
        r = b[i+1] - Ax[i+1]; // r = b - A*x
        res += r * r;
        r = b[i+2] - Ax[i+2]; // r = b - A*x
        res += r * r;
        r = b[i+3] - Ax[i+3]; // r = b - A*x
        res += r * r;
    }
    for (int i = n-rest; i < n; ++i) {
        Ax[i] = 0.0;
        for (int j = 0; j < n; ++j) {
            if (i==j || (j>i && j<i+km) || (i>j && i<j+km)) {
                Ax[i] += findVal(A,i,j) * x[j];
            }
        }
        double r = b[i] - Ax[i]; // r = b - A*x
        res += r * r;
    }
    free(Ax);
    return sqrtl(res);
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
 * Encontra valor na matriz para posição (line,col)
 * A: matriz para busca
 * line: linha da posição
 * col: coluna da posição
 **/
inline double findVal(matrix *A, int line, int col) {
    for (int i = 0; i < A->size; ++i) {
        node *n = A->nodes[i];
        if (n->line == line && n->col == col) {
            return n->val;
        }
    }
    return 0.0;
}

/**
 * Libera matriz da memória
 * A: matriz a ser liberada
 **/
inline void freeMatrix(matrix *A) {
    for (int i = 0; i < A->size; ++i) {
        free(A->nodes[i]);
    }
    free(A->nodes);
    free(A);
}

/**
 * Função que resolve Ax = b utilizando método de gradientes conjugados.
 * A: matriz de coeficientes
 * p: peso, decide matriz condicionadora
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
    if (DEBUGMSG) printf("Transformando matriz em simetrica...\n");
    matrix *ATA = malloc(sizeof(matrix));
    ATA->nodes = malloc(sizeof(node)*A->size);
    ATA->size = A->size;
    ATA->diag = A->diag;
    int km = (A->diag+1)/2;
    int index = 0;
    int limit, j, rest = n % 4; // Loop Unrolling de 4 posições
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
    if (DEBUGMSG) printf("Calculando pré-condicionadora...\n");
    double startCond = timestamp();
    matrix *M = malloc(sizeof(matrix));
    M->nodes = malloc(sizeof(node)*n);
    M->size = n;
    M->diag = 1;
    if (p == 0.0) { // Matriz Identidade
        for (int i = 0; i < n; ++i) {
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
    if (DEBUGMSG) printf("Invertendo matriz condicionadora...\n");
    inverseMatrix(M,n); // invertendo M
    // printMatrixDiagonal(M,n);
    // ----------------------------------------------------------
    if (DEBUGMSG) printf("Inicializando variáveis...\n");
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
    if (DEBUGMSG) printf("Iniciando cálculo...\n");
    LIKWID_MARKER_START("op1");
    int k;
    double meanTime = 0.0;
    for (k = 0; k < max; ++k) {
        double startTime = timestamp();
        // ----------------------------------------------------------
        // z = Av
        for (int i = 0; i < n; ++i) {
            if (i < km) {
                j = 0;
                limit = km+i;
            } else {
                j = i-km+1;
                limit = n;
            }
            z[i] = 0.0;
            for (; j < limit; ++j) {
                if (i==j || (j>i && j<i+km) || (i>j && i<j+km)) {
                    z[i] += findVal(ATA,i,j) * v[j];
                }
            }
        }
        // ----------------------------------------------------------
        // s = aux/ v^Tz
        double vtz = 0.0;
        for (int i = 0; i < n; ++i) {
            vtz += v[i] * z[i];
        }
        double s = aux/vtz;
        // ----------------------------------------------------------
        double rTr = 0.0;
        double aux1 = 0.0;
        for (int i = 0; i < n-rest; i += 4) {
            // ----------------------------------------------------------
            // x^k+1 = x^k + sv
            xant[i] = x[i];
            x[i] += (v[i] * s);
            xant[i+1] = x[i+1];
            x[i+1] += (v[i+1] * s);
            xant[i+2] = x[i+2];
            x[i+2] += (v[i+2] * s);
            xant[i+3] = x[i+3];
            x[i+3] += (v[i+3] * s);
            // ----------------------------------------------------------
            // r = r - sz
            r[i] -= (z[i] * s);
            r[i+1] -= (z[i+1] * s);
            r[i+2] -= (z[i+2] * s);
            r[i+3] -= (z[i+3] * s);
            // ----------------------------------------------------------
            // y = M^-1r
            y[i] = M->nodes[i]->val * r[i];
            y[i+1] = M->nodes[i+1]->val * r[i+1];
            y[i+2] = M->nodes[i+2]->val * r[i+2];
            y[i+3] = M->nodes[i+3]->val * r[i+3];
            // ----------------------------------------------------------
            // rTr = r^Tr
            rTr += r[i] * r[i];
            rTr += r[i+1] * r[i+1];
            rTr += r[i+2] * r[i+2];
            rTr += r[i+3] * r[i+3];
            // ----------------------------------------------------------
            // aux1 = y^Tr
            aux1 += y[i] * r[i];
            aux1 += y[i+1] * r[i+1];
            aux1 += y[i+2] * r[i+2];
            aux1 += y[i+3] * r[i+3];
        }
        for (int i = n-rest; i < n; ++i) {
            // ----------------------------------------------------------
            // x^k+1 = x^k + sv
            xant[i] = x[i];
            x[i] += (v[i] * s);
            // ----------------------------------------------------------
            // r = r - sz
            r[i] -= (z[i] * s);
            // ----------------------------------------------------------
            // y = M^-1r
            y[i] = M->nodes[i]->val * r[i];
            // ----------------------------------------------------------
            // rTr = r^Tr
            rTr += r[i] * r[i];
            // ----------------------------------------------------------
            // aux1 = y^Tr
            aux1 += y[i] * r[i];
        }
        // ----------------------------------------------------------
        fprintf(fp, "# iter %d: %.15g\n", k+1, normaMax(x,xant,n));
        if (isinf(rTr) || isnan(rTr)) {
            if (DEBUGMSG) fprintf(stderr, "ERRO: Vetor r chegou a inf ou nan!\n");
            k = -1;
            break;
        }
        double m = aux1/aux;
        aux = aux1;
        // ----------------------------------------------------------
        // v = y + mv
        for (int i = 0; i < n; ++i) {
            v[i] = y[i] + (v[i] * m);
        }
        // ----------------------------------------------------------
        double endTime = timestamp() - startTime;
        meanTime += endTime;
        if (DEBUGMSG) printf("residuo = %lf\n", rTr);
        if (rTr < erro) {
            break;
        }
    }
    LIKWID_MARKER_STOP("op1");
    // printf("meanTime = %lf, k = %d\n", meanTime, k);
    // ----------------------------------------------------------
    double startTime = timestamp();
    LIKWID_MARKER_START("op2");
    double residuo = normaEuc(A,b,x,n);
    LIKWID_MARKER_STOP("op2");
    double endTime = timestamp() - startTime;
    // ----------------------------------------------------------
    fprintf(fp, "# residuo: %.15g\n", residuo);
    fprintf(fp, "# Tempo total: %.15g\n", meanTime);
    meanTime /= k+1;
    fprintf(fp, "# Tempo iter: %.15g\n", meanTime);
    fprintf(fp, "# Tempo residuo: %.15g\n", endTime);
    fprintf(fp, "# Tempo PC: %.15g\n", endCond);
    // ----------------------------------------------------------
    freeMatrix(M);
    free(xant);
    free(y);
    free(r);
    free(v);
    free(z);
    return k;
}