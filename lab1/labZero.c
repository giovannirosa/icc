#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

int main ()
{
  Polinomio *p = (Polinomio*) malloc(sizeof(Polinomio));
  printf("Entre com o grau do polinômio: ");
  scanf("%d", &(p->grau));
  double numero;
  int i = 0;
  p->p = (double*) malloc(sizeof(double)*(p->grau+1));
  while (i <= p->grau) {
    printf("\nEntre com o próximo coeficiente do polinômio: ");
    // p->p[i] = (double*) malloc(sizeof(double));
    scanf("%lf", &p->p[i++]);
  }
  
  printf("\n\nGrau do Polinomio: %d", p->grau);
  for (i = 0; i <= p->grau; i++)
    printf("\nCoeficiente: %lf", p->p[i]);
  
  printf("\nEquação: ");
  for (i = 0; i <= p->grau; i++) {
    printf("%lfx(%d)", p->p[i], p->grau-i);
    if (i != p->grau) printf(" + ");
  }
  
  printf("\nDeu boa!\n");

  double *px = (double*) malloc(sizeof(double));
  double *dpx = (double*) malloc(sizeof(double));
  printf("\nEntre com o valor de x: ");
  double x;
  scanf("%lf", &x);
  calcPolinomio_rapido(*p,x,px,dpx);
  printf("\nResultado do Polinomio: %lf\n", *px);

  return 0;
}

