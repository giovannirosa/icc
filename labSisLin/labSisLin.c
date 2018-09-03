#include <stdio.h>
#include <math.h>
#include <string.h>

#include "utils.h"
#include "SistemasLineares.h"

int main () {
    int ordem;
    printf("Entre com a ordem do sistema linear: ");
    scanf("%d\n", &ordem);
    printf("Ordem recebida: %d\n", ordem);

    double *A = malloc(sizeof(double)*ordem*ordem);
    int i = 0;
    char coef[100];
    while (i < ordem) {
        int j = 0;
        while (j < ordem) {
            printf("\nEntre com o próximo coeficiente do sistema: ");
            scanf("%s\n", coef);
            printf("Coeficiente recebido: %s\n", coef);
            int index = (ordem * i) + j;
            A[index] = atof(coef);
            j++;
        }
        i++;
    }

    double *B = malloc(sizeof(double)*ordem);
    i = 0;
    while (i < ordem) {
        printf("\nEntre com o próximo termo independente: ");
        scanf("%s\n", coef);
        printf("Termo recebido: %s\n", coef);
        B[i++] = atof(coef);
    }

    double *X = malloc(sizeof(double)*ordem);
    i = 0;
    while (i < ordem) {
        printf("\nEntre com a próxima incógnita: ");
        scanf("%s\n", coef);
        printf("Incógnita recebido: %s\n", coef);
        X[i++] = atof(coef);
    }

    printf("Ordem do sistema: %d\n", ordem);
    printf("Matriz de coeficientes:\n");
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            int index = (ordem * i) + j;
            printf("%lf ", A[index]);
        }
        printf("\n");
    }
    printf("Incógnitas:\n");
    for (int i = 0; i < ordem; i++) {
        printf("%lf\n", X[i]);
    }
    printf("Termos independentes:\n");
    for (int i = 0; i < ordem; i++) {
        printf("%lf\n", B[i]);
    }

    double *tIteracao = malloc(sizeof(double));
    double *tTotal = malloc(sizeof(double));

    double err = jacobi(A,B,X,ordem,tIteracao,tTotal);
    if (err == -1.0) {
        printf("Esse sistema não converge para Jacobi!\n");
    } else {
        printf("Esse sistema converge para Jacobi!\n Erro: %lf | Tempo Total: %lf | Tempo por Iteração: %lf\n",err,*tIteracao,*tTotal);
    }

    err = gaussSeidel(A,B,X,ordem,tIteracao,tTotal);
    if (err == -1.0) {
        printf("Esse sistema não converge para Gauss-Seidel!\n");
    } else {
        printf("Esse sistema converge para Gauss-Seidel!\n Erro: %lf | Tempo Total: %lf | Tempo por Iteração: %lf\n",err,*tIteracao,*tTotal);
    }
}