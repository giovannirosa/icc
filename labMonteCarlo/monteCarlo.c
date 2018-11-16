#include <stdio.h>
#include <math.h>
#include <string.h>

int main (int argc, char *argv[]) {
    int n,a,b;
    for(int cont=1; cont < argc; cont++) {
        if (strcmp(argv[cont],"-h") == 0) {
            printf("O programa deve ser executado com os seguintes parâmetros:\n");
            printf("cgSolver -n <n> -a <a> -b <b>\n");
            printf("<n>: número de dimensões.\n");
            printf("<a>: início do intervalo [a,b].\n");
            printf("<b>: fim do intervalo, onde a < b.\n");
            return 0;
        }

        if (strcmp(argv[cont],"-n") == 0) {
            n = (int) strtol(argv[++cont], (char **)NULL, 10);
            if (n < 1) {
                fprintf(stderr, "ERRO: Parâmetro n deve ser maior que 0!\n");
                return 1;
            }
        }
        if (strcmp(argv[cont],"-a") == 0) {
            a = (int) strtol(argv[++cont], (char **)NULL, 10);
            if (a < 0) {
                fprintf(stderr, "ERRO: Parâmetro a deve ser >= 0!\n");
                return 1;
            }
        }
        if (strcmp(argv[cont],"-b") == 0) {
            b = (int) strtol(argv[++cont], (char **)NULL, 10);
            if (b < a) {
                fprintf(stderr, "ERRO: Parâmetro b deve ser maior que a!\n");
                return 1;
            }
        }

        

    }




    srand(1234);
}

double styblinskiTang(double *x, int n) {
    double soma = 0.0;
    for (int i = 0; i < n; i++) {
        double square = x[i] * x[i];
        soma += (square * square) - 16 * (square) + 5 * x[i];
    }
    return soma / 2;
}

void trapezios(double *x, int p, int n) {
    for (int i = 0; i < n; i++) {
        
    }
}